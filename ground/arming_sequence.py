# Credit: Martin Starkov
# Only tested and supported on Windows 10 (until I become less lazy), Unix will likely not work due to msvcrt module and clear()

import msvcrt
import os
import time
import serial

lines = "----------------------" # separator for console prints
state_error = "not connected"

class Arming():

    def __init__(self, arming_speed): # arming_speed represents the multiplier on hard-coded "modest" arming speed of "1"
        self.bt = 0
        self.main(arming_speed)

    def clear(self): # clear console
        _ = os.system('cls')

    def line_print(self, strings): # print array object separated by lines from below
        for i in strings:
            print(i)
            print(lines)

    def confirmation(self, string, second=False): # user input arming confirmation
        self.clear()
        print(string) # ask for confirmation

        command = msvcrt.getwch().upper() # user input

        # input paths
        if command == 'Y' and second: # second y -> arm
            return
        elif command == 'Y': # first y -> reconfirmation
            return self.confirmation("Are you sure you want to arm Darwin? ('y' to confirm, 'n' to cancel): ", True)
        elif command == 'N': # any n -> cancellation
            raise SystemExit
        elif second: # first y + other key stroke -> reconfirmation
            return self.confirmation("Are you sure you want to arm Darwin? ('y' to confirm, 'n' to cancel): ", True)
        else: # other key stroke -> initial confirmation
            return self.confirmation(string)

    def arming_sequence(self, time_step): # occurs after successful confirmation

        arming = True
        counter = 0 # arming %

        while arming:
            self.clear()
            print("Arming Darwin... (" + str(counter) + "%)" + " ('n' to cancel)") # print arming %

            # arming complete
            if counter >= 100:
                arming = False
                return True # ready

            # user input
            while msvcrt.kbhit():
                if msvcrt.getwch().upper() == "N":
                    print(lines)
                    self.line_print(["Disarming Darwin..."])
                    arming = False
                    return False # disarm

            # continue incrementing arming sequence
            counter += 1
            time.sleep(time_step)

    def init_bluetooth(self, com, baud):
        try:
            self.bt = serial.Serial(port=com, baudrate=baud)
            if self.bt.is_open:
                print("Successfully opened bluetooth serial on " + self.bt.name)
            else:
                print("Could not find " + com)
        except:
            raise Exception
        time.sleep(3)

    def init_darwin(self): # bluetooth serial initalization among other things
        self.init_bluetooth('COM6', 9600)

    def read_bluetooth(self):
            while True:
                c = self.bt.read(1)
                if c != b'':
                    response = str(c).strip("b").strip("'")
                    while True:
                        char = self.bt.read(1)
                        if char == b'\n':
                            break
                        response = response + str(char).strip("b").strip("'")
                    response = response.replace("\\n", "").replace("\\r", "")
                    break
            return response

    def sensor_data(self, counter):
        # W.I.P, eventually use bluetooth data here
        processed_data = self.old_data.split(";")
        if len(processed_data) > 9:
            print("BMP Temperature:", processed_data[0])
            print("Pressure:", processed_data[1])
            print("Altitude:", processed_data[2])
            print("BNO Temperature:", processed_data[3])
            print("Orientation:", processed_data[4])
            print("Angular Velocity:", processed_data[5])
            print("Linear Acceleration:", processed_data[6])
            print("Net Acceleration:", processed_data[7])
            print("Gravity:", processed_data[8])
            print("Magnetic Field:", processed_data[9])
        data = self.read_bluetooth()
        if data != "":
            self.old_data = data

    def sensor_states(self, counter):
        # W.I.P, eventually use bluetooth to retrieve active sensor states here
        print("Bluetooth output:", self.read_bluetooth())
        print("BMP280-1:", state_error)
        print("BMP280-2:", state_error)
        print("BMP280-3:", state_error)
        print("BNO055:", state_error)
        print("GPS:", state_error)

    def parachute_states(self, counter):
        # W.I.P, eventually use bluetooth to retrieve parachute states here
        print("Bluetooth output:", self.read_bluetooth())
        print("Main:", state_error)
        print("Drogue:", state_error)

    def main(self, arming_speed): # call this

        self.confirmation("Arm Darwin ('y' to confirm, 'n' to cancel): ")

        if self.arming_sequence(0.1 / arming_speed): # multiplier on what I consider a good arming speed for "1"

            # initialization
            self.init_darwin()
            command = "armed"
            c = command # this is the last interpreted command (cached so prints work even when no command is entered)
            counter = 0
            sending_sensor_data = False
            self.old_data = ""

            while True: # cycle loop
                try:


                    # initial arming confirmation
                    if c == "armed":
                        self.line_print(["Darwin armed successfully"])

                    # help menu
                    if c == "H": # return to help menu
                        self.line_print(["'i' for fc init call", "'d' for data output", "'s' for sensor states", "'p' for parachute states", "'c' for clear view", "'q' to quit script"])
                    else:
                        # print this every cycle so user never gets lost
                        self.line_print(["Cycle: #" + str(counter), "Use 'h' for list of commands"])

                    # other commands
                    if c == "I":
                        self.line_print(["Init status"])
                        self.bt.write("i".encode("utf-8"))
                        print("Bluetooth output:", self.read_bluetooth())
                    elif c == "D":
                        #self.bt.write("d".encode("utf-8"))
                        if not sending_sensor_data:
                            self.bt.write("d".encode("utf-8"))
                            sending_sensor_data = True
                        self.line_print(["Sensor data"])
                        self.sensor_data(counter)
                    elif c == "S":
                        self.line_print(["Sensor states"])
                        self.sensor_states(counter)
                    elif c == "P":
                        self.line_print(["Parachute states"])
                        self.parachute_states(counter)
                    elif c == "Q":
                        print("Exiting script")
                        raise SystemExit
                    # user input
                    while msvcrt.kbhit():
                        command = msvcrt.getwch().upper()
                        break

                    c = command # cache previous interpreted command

                    time.sleep(0.1) # delay

                    counter += 1 # increment cycle
                    self.clear() # refresh console

                except:

                    raise SystemExit
        else:
            print("Darwin disarmed successfully")

arming = Arming(5)