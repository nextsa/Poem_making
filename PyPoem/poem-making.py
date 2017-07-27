import threading

def writer(x, event_for_wait, event_for_set):
    for i in x:
        event_for_wait.wait() # wait for event
        event_for_wait.clear() # clean event for future
        print(i)
        event_for_set.set() # set event for neighbor thread

with open("f1.txt", 'r', encoding='utf-8') as fin:
    line = [row.strip() for row in fin]

with open("f2.txt", 'r', encoding='utf-8') as fin:
    sline = [row.strip() for row in fin]


# init events
e1 = threading.Event()
e2 = threading.Event()

# init threads
t1 = threading.Thread(target=writer, args=(line, e1, e2))
t2 = threading.Thread(target=writer, args=(sline, e2, e1))

# start threads
t1.start()
t2.start()

e1.set() # initiate the first event

# join threads to the main thread
t1.join()
t2.join()
