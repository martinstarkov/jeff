import serial

def bluetooth_listener(com, baud):
    bt = serial.Serial(port=com, baudrate=baud)
    if bt.is_open:
        print("Successfully opened bluetooth serial on " + bt.name)
    else:
        print("Could not find " + com)
        return
    cycle = 0
    while True:
        mode = input("Enter mode input (init / regular): ")
        bt.write(mode.encode("utf-8"))
        if mode == "init" or mode == "regular":
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
                    print("Computer: " + response)
                    break
        cycle += 1

bluetooth_listener('COM6', 9600)

