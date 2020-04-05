import threading
import time
import queue

input_queue = queue.Queue()
command_input_event = threading.Event()

def kbdListener():
    global input_queue, command_input_event
    kbdInput = ''
    while kbdInput.lower() not in ['quit', 'exit', 'stop']:
        kbdInput = input("> ")
        input_queue.put(kbdInput)
        command_input_event.set()
        input_queue.join()

listener = threading.Thread(target=kbdListener)
listener.start()
stop = False
while not stop:
    if command_input_event.is_set():
        while not input_queue.empty():
            command = input_queue.get()
            if command.lower() in ['quit', 'exit', 'stop']:
                print('Stopping')
                while not input_queue.empty():
                    input_queue.get()
                    input_queue.task_done()
                input_queue.task_done()
                stop = True
                break
            else:
                print('Command "{}" received and processed'.format(command))
                input_queue.task_done()