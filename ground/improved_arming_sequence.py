import threading
import time
import queue
import msvcrt
import os

input_queue = queue.Queue()
command_input_event = threading.Event()

def kbdListener():
    global input_queue, command_input_event
    kbdInput = ''
    while kbdInput.lower() not in ['q']:
        kbdInput = msvcrt.getwch()
        input_queue.put(kbdInput)
        command_input_event.set()
        input_queue.join()


os.system('cls')
listener = threading.Thread(target=kbdListener)
listener.start()
stop = False
data = True
refresh = data
counter = 0
old_data = data
old_refresh = refresh
old_counter = counter
quit = False
while not stop:
    if command_input_event.is_set():
        while not input_queue.empty():
            command = input_queue.get()
            if command.lower() in ['i', 'h']:
                os.system('cls')
                print("'start data' to view data ouput\n'stop data' to close data output\n'back' to leave command input\n'quit' to stop the script")
                print("-------------")
                print("Command input:\n-------------")
                user_input = input("")
                os.system('cls')
                if user_input == "stop data":
                    data = False
                    refresh = False
                    counter = 0
                elif user_input == "start data":
                    refresh = True
                    data = True
                elif user_input == "quit":
                    os.system('cls')
                    while not input_queue.empty():
                        input_queue.get()
                        input_queue.task_done()
                    input_queue.task_done()
                    stop = True
                    quit = True
                    print('Quitting script...')
                    break
                elif user_input == "back":
                    os.system('cls')
                    data = old_data
                    refresh = old_refresh
                    counter = 0
                else:
                    os.system('cls')
                    data = old_data
                    refresh = old_refresh
                    counter = 0
            input_queue.task_done()
    if not quit:
        if refresh:
            print("'i' for command input\n-------------")
        elif counter == 0 and not refresh:
            os.system('cls')
            print("'i' for command input\n-------------")
            counter += 1
        if data:
            print("Data\n-------------\nBMP: 123\nBNO: 456")
        time.sleep(0.1)
        if refresh:
            os.system('cls')
    else:
        raise SystemExit


