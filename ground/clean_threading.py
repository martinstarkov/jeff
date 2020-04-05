import threading
import time
import queue
import os
import sys
import serial

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
        if char == b'\x03':
            print("Ctrl+C")
            raise KeyboardInterrupt
        elif char == b'\x04':
            print("Ctrl+D")
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
        return ch.encode('utf-8')

class _GetchWindows: # windows getch implementation
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getwch().encode('utf-8')

class Darwin(object): # arming object
    def __init__(self, com): # variable initalization
        self.running = True
        self.port = com
        self.baud = 9600
        self.bt_line = ""
        self.handling_input = False
        self.getch = _Getch() # getch object
        self.getch_thread = threading.Thread(target=self.getch_threading, daemon=True)
        self.bluetooth_thread = threading.Thread(target=self.bluetooth_threading, daemon=True)

    def __call__(self):
        clear()
        print("Initializing script")
        time.sleep(1)
        self.connection_confirmation()
        self.cycle()

    def cycle(self):
        counter = 1
        while self.running:
            if self.bt: # real bluetooth connection
                if self.bt_line:
                    print("bt: " + self.bt_line)
            else: # fake bluetooth connection
                print("fake bt: " + self.bt_line)
            counter += 1
            if counter > 10000:
                self.running = False

    def connection_confirmation(self):
        while True:
            clear()
            confirmation = input("-------------------------- \n"
                                "Connect to Darwin? \n"
                                "'y' -> yes \n"
                                "'f' -> fake bt connection \n"
                                "'n' -> no \n"
                                "-------------------------- \n")
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
            continue

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

    def bluetooth_threading(self):
        print("Bluetooth thread opened")
        while self.running:
            try:
                self.bt_line = self.bt.readline()
                if self.bt_line == b'' or self.bt_line == "":
                    self.bt_line = None
            except:
                print("Bluetooth thread closed - exception Occured")
                self.running = False

    def getch_threading(self):
        pass

darwin = Darwin('COM6')
darwin()

