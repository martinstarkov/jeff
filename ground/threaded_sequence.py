import threading
import time
import queue
import os
import sys

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
        import sys, termios    #for linux/unix
        termios.tcflush(sys.stdin, termios.TCIOFLUSH)

try:
    from msvcrt import kbhit
except ImportError:
    import termios, fcntl, sys, os
    def kbhit():
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

while True:
    clear()
    confirmation = input("------------------------- \nConnect to Darwin? (y/n): \n------------------------- \n")
    if len(confirmation) > 0:
        if confirmation[0] == "y":
            break
        elif confirmation[0] == "n" or confirmation[0] == "q":
            raise SystemExit
    continue

getch = _Getch()
lock = threading.Lock()
data = False
stop = False
jeff = False
cycle = 0
print_delay = 1 # 0.5 # print output delay, seconds
arming_delay = 0 # 0.05 # slow down arming speed, seconds
raw_data_points = 15 # amount of raw data points being sent by teensy data output
null_data_message = "not connected"

clear()

for i in range(0,100):
    while kbhit():
        if getch().decode("utf-8") == "q":
            raise SystemExit
    clear()
    print("------------------------------------------- \nConnecting to Darwin... (" + str(i) + "%) ('q' to quit) \n-------------------------------------------")
    time.sleep(arming_delay)

flush_input()
arming_status = True

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
    global raw_data_points, null_data_message
    raw_data = [""] * raw_data_points
    for i in range(len(raw_data)):
        if raw_data[i] == "":
            raw_data[i] = null_data_message
    return raw_data

def print_data():
    global cycle
    raw_data = process_data_packet()
    print("Cycle #" + str(cycle) + "\n----------------------------\n" + "Altitude (BMP1): " + raw_data[0] + "\n" + "Altitude (BMP2): " + raw_data[1] + "\n" + "Altitude (BMP3): " + raw_data[2] + "\n" + "Temperature (BMP1): " + raw_data[3] + "\n" + "Temperature (BMP2): " + raw_data[4] + "\n" + "Temperature (BMP3): " + raw_data[5] + "\n" + "Pressure (BMP1): " + raw_data[6] + "\n" + "Pressure (BMP2): " + raw_data[7] + "\n" + "Pressure (BMP3): " + raw_data[8] + "\n" + "Orientation (BNO): " + raw_data[9] + "\n" + "Angular Velocity (BNO): " + raw_data[10] + "\n" + "Linear Acceleration (BNO): " + raw_data[11] + "\n" + "Net Acceleration (BNO): " + raw_data[12] + "\n" + "Gravitational Acceleration (BNO): " + raw_data[13] + "\n" + "Magnetic Field (BNO): " + raw_data[14])
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

clear()

output_thread = threading.Thread(target=f_output, daemon=True)
input_thread = threading.Thread(target=f_input, daemon=True)

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
        raise SystemExit
