import threading
import time
import queue
import os
import sys
import serial

def clear():
    if os.name == 'nt':
        os.system('cls||echo -e \\\\033c')
    else:
        os.system('clear||echo -e \\\\033c') # change if this doesn't work on Unix systems

def flush_input():
    try:
        import msvcrt
        while msvcrt.kbhit():
            msvcrt.getch()
    except ImportError:
        import sys, termios #for linux/unix
        termios.tcflush(sys.stdin, termios.TCIOFLUSH)

def kbfunc():
    #this is boolean for whether the keyboard has bene hit
    try:
        import msvcrt
        return msvcrt.kbhit()
    except ImportError: #for linux/unix
        import termios, fcntl, sys, os
        fd = sys.stdin.fileno()
        oldterm = termios.tcgetattr(fd)
        newattr = termios.tcgetattr(fd)
        newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
        termios.tcsetattr(fd, termios.TCSANOW, newattr)
        oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
        fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
        try:
            while True:
                try:
                    c = sys.stdin.read(1)
                    return True
                except IOError:
                    return False
        finally:
            termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
            fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)

# try:
#     from msvcrt import kbhit
# except ImportError:
#     import termios, fcntl, sys, os
#     def kbhit():
#         fd = sys.stdin.fileno()
#         oldterm = termios.tcgetattr(fd)
#         newattr = termios.tcgetattr(fd)
#         newattr[3] = newattr[3] & ~termios.ICANON & ~termios.ECHO
#         termios.tcsetattr(fd, termios.TCSANOW, newattr)
#         oldflags = fcntl.fcntl(fd, fcntl.F_GETFL)
#         fcntl.fcntl(fd, fcntl.F_SETFL, oldflags | os.O_NONBLOCK)
#         try:
#             while True:
#                 try:
#                     c = sys.stdin.read(1)
#                     return True
#                 except IOError:
#                     return False
#         finally:
#             termios.tcsetattr(fd, termios.TCSAFLUSH, oldterm)
#             fcntl.fcntl(fd, fcntl.F_SETFL, oldflags)

# Getch code is a modified version of http://code.activestate.com/recipes/134892/
# Created by stackoverflow user /2734389/kiri
# Found from https://stackoverflow.com/questions/510357/python-read-a-single-character-from-the-user

class _Getch:
    """Gets a single character from standard input.  Does not echo to the screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): 
        char = self.impl()
        if char == b'\x03':
            print("Ctrl+C")
            raise KeyboardInterrupt
        elif char == b'\x04':
            print("Ctrl+D")
            raise EOFError
        return char

class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch.encode('utf-8')

class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getwch().encode('utf-8')

bt_usage = True

while True:
    clear()
    confirmation = input("------------------------- \nConnect to Darwin? \n'y' -> yes \n'f' -> yes and fake BT connection, for script testing purposes \n'n' -> no \n------------------------- \n")
    if len(confirmation) > 0:
        if confirmation[0] == "y":
            break
        elif confirmation[0] == "n" or confirmation[0] == "q":
            raise SystemExit
        elif confirmation[0] == "f":
            bt_usage = False
            break
    continue

clear()

getch = _Getch()
lock = threading.Lock()
data = False
stop = False
jeff = False
bt_status = False
bt_complete = False
bt_read = ""
cycle = 0
print_delay = 1 # 0.5 # print output delay, seconds
arming_delay = 0.05 # 0.05 # slow down arming speed, seconds
raw_data_points = 15 # amount of raw data points being sent by teensy data output
bt_fake_signal = "1;2;3;4;5;6;7;8;9;10;"
null_data_message = "null"
undefined_data_message = "unreceived value"
port = 'COM6'
baud = 9600
bt = None

def determine_action(c):
    global stop, data, jeff
    if c == "start data":
        data = True
    elif c == "stop data":
        data = False
    elif c == "jeff":
        jeff = True
    elif c == "quit":
        stop = True

def f_input():
    global stop, arming_status
    while not stop:
        try:
            getch_input = getch()
            key = getch_input.decode("utf-8")
            if key == "i":
                arming_status = False
                lock.acquire()
                clear()
                print("--------------------------------- \n'start data' to view data ouput \n'stop data' to close data output \n'quit' to stop the script \n--------------------------------- \nCommand input: \n---------------------------------")
                try:
                    command = input("").lower().strip()
                except:
                    lock.release()
                determine_action(command)
                clear()
                lock.release()
            elif key == "q":
                raise Exception
        except:
            stop = True
            print("Input Termination Occured")
            break
    print("Closing Input Thread")

def process_data_packet():
    global raw_data_points, null_data_message, undefined_data_message
    data_packet = bt_read
    if data_packet == "" or data_packet.count(";") == 0:
        raw_data = [null_data_message] * raw_data_points
    else:
        data_packet = data_packet.strip(";").split(";")
        difference = abs(len(data_packet) - raw_data_points)
        if difference > 0:
            raw_data = data_packet
            for i in range(difference):
                raw_data.append(undefined_data_message)
        elif difference < 0:
            raw_data = []
            for i in range(raw_data_points):
                raw_data.append(data_packet[i])
    return raw_data

def print_data():
    global cycle, bt_read
    raw_data = process_data_packet()
    data_string = "Cycle #" + str(cycle) + "\n----------------------------\n"
    data_string += "Raw Bluetooth Read: " + bt_read + "\n"
    data_string += "Altitude (BMP1): " + raw_data[0] + "\n"
    data_string += "Altitude (BMP2): " + raw_data[1] + "\n"
    data_string += "Altitude (BMP3): " + raw_data[2] + "\n"
    data_string += "Temperature (BMP1): " + raw_data[3] + "\n"
    data_string += "Temperature (BMP2): " + raw_data[4] + "\n"
    data_string += "Temperature (BMP3): " + raw_data[5] + "\n"
    data_string += "Pressure (BMP1): " + raw_data[6] + "\n"
    data_string += "Pressure (BMP2): " + raw_data[7] + "\n"
    data_string += "Pressure (BMP3): " + raw_data[8] + "\n"
    data_string += "Orientation (BNO): " + raw_data[9] + "\n"
    data_string += "Angular Velocity (BNO): " + raw_data[10] + "\n"
    data_string += "Linear Acceleration (BNO): " + raw_data[11] + "\n"
    data_string += "Net Acceleration (BNO): " + raw_data[12] + "\n"
    data_string += "Gravitational Acceleration (BNO): " + raw_data[13] + "\n"
    data_string += "Magnetic Field (BNO): " + raw_data[14]
    print(data_string)
    cycle += 1

def f_output():
    global data, stop, jeff, cycle, print_delay, arming_status
    command = ""
    while not stop:
        try:
            if not lock.locked():
                clear()
                if arming_status:
                    print("---------------------------- \nDarwin Connection Successful")
                print("----------------------------\n'i' for input, 'q' for quit \n----------------------------")
                if data and not lock.locked():
                    print_data()
                if jeff and not lock.locked():
                    jeff = False
                    # ascii_path = "jeff.txt"
                    # # # uncomment if pygame module is installed and you have a valid sound file in the directory
                    # # music_path = "jeff.mp3"
                    # # from pygame import mixer  # Load the popular external library
                    # # mixer.init()
                    # # mixer.music.load(music_path)
                    # # mixer.music.play()
                    # # time.sleep(3.5)
                    # f = open(ascii_path)
                    # lines = f.read().splitlines()
                    # f.close()
                    # for line in lines:
                    #     print(line)
                    print("A curious one I see ;)")
                    time.sleep(1)
                time.sleep(print_delay)
        except:
            print("Output Termination Occured")
            break
    print("Closing Output Thread")

def f_bluetooth():
    global port, baud, stop, bt, bt_status, bt_read, bt_complete, bt_usage, bt_fake_signal
    while not stop:
        if not bt_status:
            if bt_usage:
                print("Connecting to Bluetooth... ('q' to quit)")
                time.sleep(1)
                try:
                    bt = serial.Serial(port=port, baudrate=baud)
                    if bt.is_open:
                        print("Successfully opened bluetooth serial on " + bt.name)
                        bt_status = True
                    else:
                        print("Could not find " + port)
                    bt_complete = True
                except:
                    print("Bluetooth Initialization Exception Occured")
                    bt_complete = True
                    stop = True
                    break
            else:
                bt_complete = True
                bt_status = True
                bt_read = bt_fake_signal
        elif bt_complete and bt_usage:
            try:
                response = ""
                while True:
                    c = bt.read(1)
                    if c != b'':
                        response = str(c).strip("b").strip("'")
                        while True:
                            char = bt.read(1)
                            if char == b'\n':
                                break
                            response = response + str(char).strip("b").strip("'")
                        response = response.replace("\\n", "").replace("\\r", "")
                        break
                bt_read = response
            except:
                print("Bluetooth Read Exception Occured")
                stop = True
                break
        else: # bluetooth not in use (for testing script)
            pass
    print("Closing Bluetooth Thread")

output_thread = threading.Thread(target=f_output, daemon=True)
input_thread = threading.Thread(target=f_input, daemon=True)
bluetooth_thread = threading.Thread(target=f_bluetooth, daemon=True)

bluetooth_thread.start()

bt_connect_timer = 0

while not bt_complete: # check for 'q' input to quit
    while kbfunc():
        if getch().decode("utf-8") == "q":
            raise SystemExit
    #clear()
    #print("------------------------------------------- \nConnecting to Darwin... (" + str(bt_connect_timer) + " cycles since start) ('q' to quit) \n-------------------------------------------")
    bt_connect_timer += 1
    time.sleep(arming_delay)

if bt_status:

    flush_input()
    arming_status = True

    clear()

    input_thread.start()
    output_thread.start()

    while True:
        try:
            if input_thread.is_alive():
                continue
            else:
                lock.acquire()
                raise SystemExit
        except:
            input_thread.join()
            output_thread.join()
            bluetooth_thread.join()
            raise SystemExit

else:
    raise SystemExit
