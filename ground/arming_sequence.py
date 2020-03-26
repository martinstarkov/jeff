# Credit: Martin Starkov
# Only tested and supported on Windows 10 (until I become less lazy), Unix will likely not work due to msvcrt module and clear()

import msvcrt
import os
import time

lines = "----------------------" # separator for console prints
state_error = "not connected"

def clear(): # clear console
    _ = os.system('cls')

def line_print(strings): # print array object separated by lines from below
    for i in strings:
        print(i)
        print(lines)

def confirmation(string, second=False): # user input arming confirmation
    clear()
    print(string) # ask for confirmation

    command = msvcrt.getwch().upper() # user input

    # input paths
    if command == 'Y' and second: # second y -> arm
        return
    elif command == 'Y': # first y -> reconfirmation
        return confirmation("Are you sure you want to arm Darwin? ('y' to confirm, 'n' to cancel): ", True)
    elif command == 'N': # any n -> cancellation
        raise SystemExit
    elif second: # first y + other key stroke -> reconfirmation
        return confirmation("Are you sure you want to arm Darwin? ('y' to confirm, 'n' to cancel): ", True)
    else: # other key stroke -> initial confirmation
        return confirmation(string)

def arming_sequence(time_step): # occurs after successful confirmation

    arming = True
    counter = 0 # arming %

    while arming:
        clear()
        print("Arming Darwin... (" + str(counter) + "%)" + " ('n' to cancel)") # print arming %

        # arming complete
        if counter >= 100:
            arming = False
            return True # ready

        # user input
        while msvcrt.kbhit():
            if msvcrt.getwch().upper() == "N":
                print(lines)
                line_print(["Disarming Darwin..."])
                arming = False
                return False # disarm

        # continue incrementing arming sequence
        counter += 1
        time.sleep(time_step)

def init_darwin(): # bluetooth serial initalization among other things
    # W.I.P
    pass

def sensor_data(counter):
    # W.I.P, eventually use bluetooth data here
    print("Altitude:", state_error)
    print("Pressure:", state_error)
    print("Temperature:", state_error)
    print("Orientation:", state_error)
    print("Linear Acceleration:", state_error)

def sensor_states(counter):
    # W.I.P, eventually use bluetooth to retrieve active sensor states here
    print("BMP280-1:", state_error)
    print("BMP280-2:", state_error)
    print("BMP280-3:", state_error)
    print("BNO055:", state_error)
    print("GPS:", state_error)

def parachute_states(counter):
    # W.I.P, eventually use bluetooth to retrieve parachute states here
    print("Main:", state_error)
    print("Drogue:", state_error)

def main(arming_speed): # call this

    confirmation("Arm Darwin ('y' to confirm, 'n' to cancel): ")

    if arming_sequence(0.1 / arming_speed): # multiplier on what I consider a good arming speed for "1"

        # initialization
        init_darwin()
        command = "armed"
        c = command # this is the last interpreted command (cached so prints work even when no command is entered)
        counter = 0

        while True: # cycle loop
            try:

                clear() # refresh console

                # initial arming confirmation
                if c == "armed":
                    line_print(["Darwin armed successfully"])

                # help menu
                if c == "H": # return to help menu
                    line_print(["'d' for data output", "'s' for sensor states", "'p' for parachute states", "'c' for clear view", "'q' to quit script"])
                else:
                    # print this every cycle so user never gets lost
                    line_print(["Cycle: #" + str(counter), "Use 'h' for list of commands"])

                # other commands
                if c == "D":
                    line_print(["Sensor data"])
                    sensor_data(counter)
                elif c == "S":
                    line_print(["Sensor states"])
                    sensor_states(counter)
                elif c == "P":
                    line_print(["Parachute states"])
                    parachute_states(counter)
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

            except:

                raise SystemExit
    else:
        print("Darwin disarmed successfully")

if __name__ == "__main__": # initial call
    main(2) # number represents the multiplier on hard-coded "modest" arming speed of "1"