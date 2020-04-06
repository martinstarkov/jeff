import threading
import time
import queue
import os
import sys
import serial
import json

def clear(): # clear console command
    if os.name == 'nt':
        os.system('CLS')
    else:
        os.system('clear')

def flush_input(): # flush getch
    try:
        import msvcrt
        while msvcrt.kbhit():
            msvcrt.getch()
    except ImportError: # for unix os
        import sys, termios
        termios.tcflush(sys.stdin, termios.TCIOFLUSH)

def key_press(): # boolean for key press
    try:
        import msvcrt
        return msvcrt.kbhit()
    except ImportError: # for unix os
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

class _Getch: # get single char from input
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): 
        char = self.impl()
        if char.encode('utf-8') == b'\x03':
            print("Ctrl+C termination")
            raise KeyboardInterrupt
        elif char.encode('utf-8') == b'\x04':
            print("Ctrl+D termination")
            raise EOFError
        return char

class _GetchUnix: # unix getch implementation
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
        return ch

class _GetchWindows: # windows getch implementation
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getwch()

class Darwin(object): # arming object
    def __init__(self, com): # variable initalization
        self.running = True
        self.port = com
        self.baud = 9600
        self.bt_line = '{ \
                        "debug": ["SUCCESS: This happened", "FAILURE: This other thing happened", "NEUTRAL: Idc"], \
                        "data": \
                        { \
                            "pressure": [1, 2, 3], \
                            "temperature": [2, 3, 4] \
                        }, \
                        "statuses": \
                        { \
                            "airbrakes_work": true, \
                            "main_chutes_work": true, \
                            "drogue_chutes_work": true \
                        } \
                        }'
        self.bt_json = json.loads(self.bt_line)
        self.debug_json = None
        self.debug_message = ""
        self.separator = "-----------------------------------------"
        self.commands = ["init darwin", "sensor data", "statuses"]
        self.getch_commands = ['i', 'q']
        self.data = True
        self.getch = _Getch() # getch object
        self.getch_thread = threading.Thread(target=self.getch_threading, daemon=True)
        self.bluetooth_thread = threading.Thread(target=self.bluetooth_threading, daemon=True)

    def __call__(self):
        clear()
        print("Initializing script")
        time.sleep(1)
        self.connection_confirmation()
        self.cycle()

    def quit(self):
        print("Termination program")
        self.running = False

    def cycle(self):
        self.cycle = 0
        self.getch_thread.start()
        while self.running:
            try:
                clear()
                print("'i' for input, 'q' to quit")
                if self.data:
                    print(self.separator)
                    print("Data Output:")
                    print(self.separator)
                    print("BMP: 1")
                self.update_debug()
                print(self.separator)
                print("Bluetooth Debug:")
                print(self.separator)
                print(self.debug_message)
                print(self.separator)
                if self.pressed_key == 'q':
                    self.quit()
                while self.pressed_key == 'i' and self.running:
                    clear()
                    print(self.separator)
                    print("'init darwin' to initialize teensy")
                    print("'sensor data' will toggle sensor data printing")
                    print("'statuses' will toggle parachute and airbrake status printing")
                    self.command = input(self.separator + "\n"
                                        "Command Input: \n"
                                        + self.separator + "\n")
                    if self.command in self.commands:
                        if self.command == "sensor data":
                            if self.data:
                                self.data = False
                            else:
                                self.data = True
                        if self.bt:
                            if self.command == "init darwin":
                                pass # write to bluetooth
                        clear()
                        self.pressed_key = ''
                if self.bt: # real bluetooth connection
                    if self.bt_line:
                        print("bt: " + self.bt_line)
                self.cycle += 1
                self.debug_json = self.bt_json["debug"]
                time.sleep(0.1)
            except KeyboardInterrupt:
                print("Ctrl+C termination")
                self.running = False
            except EOFError:
                print("Ctrl+D termination")
                self.running = False

    def connection_confirmation(self):
        while True:
            clear()
            confirmation = input(self.separator + "\n"
                                "Connect to Darwin? \n"
                                "'y' -> yes \n"
                                "'f' -> fake bt connection \n"
                                "'n' -> no \n"
                                + self.separator + "\n")
            clear()
            if len(confirmation) > 0:
                if confirmation[0] == "y":
                    self.connect_bt()
                    self.bluetooth_thread.start()
                    break
                elif confirmation[0] == "n":
                    raise SystemExit
                elif confirmation[0] == "f":
                    self.bt = None
                    print("Fake bluetooth connection to Darwin successful")
                    break

    def connect_bt(self):
        try:
            self.bt = serial.Serial(port=self.port, baudrate=self.baud)
            if self.bt.is_open:
                print("Bluetooth connection to Darwin successful on serial port " + self.bt.name)
            else:
                print("Bluetooth could not open " + self.port)
        except:
            self.bt = serial.Serial()
            print("Bluetooth connection failed - exception occured")
            raise SystemExit

    def update_debug(self):
        try:
            if self.debug_json != self.bt_json["debug"]:
                self.debug_message = ""
                for num, entry in enumerate(self.bt_json["debug"]):
                    if num == len(self.bt_json["debug"]) - 1: # no newline for last element of array
                        self.debug_message += entry
                    else:
                        self.debug_message += entry + "\n"
        except Exception as e:
            print(e)
            print("JSON reader failure - exception occured")
            self.running = False

    def bluetooth_threading(self):
        print("Bluetooth thread opened")
        while self.running:
            try:
                self.bt_line = self.bt.readline()
                if self.bt_line == b'' or self.bt_line == "":
                    self.bt_line = None
                    self.bt_json = None
                else:
                    self.bt_json = json.loads(self.bt_line)
            except:
                print("Bluetooth thread closed - exception occured")
                self.running = False

    def getch_threading(self):
        self.pressed_key = ''
        while self.running:
            try:
                if self.pressed_key not in self.getch_commands:
                    key = self.getch()
                    if key.encode("utf-8") == b'\r' or key.encode("utf-8") == b'\n': # consider enter presses as invalid input
                        self.pressed_key = ''
                    elif key != '':
                        self.pressed_key = key.lower()
                else:
                    flush_input()
            except:
                print("Getch thread closed - exception occured")
                self.running = False

darwin = Darwin('COM6')
darwin()

