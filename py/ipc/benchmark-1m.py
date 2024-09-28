from socketipc import *
import math
import time
import random

LINE_ERASE = "\x1b[1A\x1b[2K"
if __name__ == "__main__" :
    cli = IPCClient(addr='socket_ipc')
    iid = int(cli.create_instance().value)
    print(f"Instance ID {iid}")
    error = 0.0
    start = time.time()
    test_stream	= []
    i = 0
    with open("./ml-1m/ratings.dat", "r") as f :
        lines = f.readlines()
        for l in lines :
            s = l.split("::")
            uid = int(s[0])
            id  = int(s[1])
            val = ((float(s[2]) - 1) / 4) * 2 - 1
            if random.random() < 0.80 :
                cli.train_stream(iid, uid, id, val)
            else :
                test_stream.append((uid, id, val))
            print(f'Processing dataset {(i / 10_002.09):.2f}%\n', end=LINE_ERASE)
            i += 1
    print(f'Test split size : {len(test_stream)}')
    i = 0
    for t in test_stream :
        id = t[1]
        uid = t[0]
        real = 1 + (1 + t[2]) / 2 * 4
        ret = cli.eval(iid, uid, id).value
        ret = 1 + (ret) * 4
        error += (ret - real) ** 2
        i += 1
        cli.train_stream(iid, uid, id, ((real - 1) / 4) * 2 - 1)
        print(f"{(i / len(test_stream))*100:.2f}%\t{ret:.2f} - {real:.2f}\t{math.sqrt(error/i):.4f}\n", end='')
    print(f"RMSE = {math.sqrt(error/i)}")
    total = (time.time() - start)/i * 1000
    cli.save(iid=iid)