from socketipc import *
import math
import time

LINE_ERASE = "\x1b[1A\x1b[2K"
if __name__ == "__main__" :
    cli = IPCClient()
    iid = int(cli.create_instance().value)
    print(f"Instance ID {iid}")
    error = 0.0
    start = time.time()
    with open("./ml-100k/u1.base", "r") as f :
        lines = f.readlines()
        for l in lines :
            s = l.split("\t")
            uid = int(s[0])
            id  = int(s[1])
            val = ((float(s[2]) - 1) / 4) * 2 - 1
            cli.train_stream(iid, uid, id, val)
    with open("./ml-100k/u1.test", "r") as f :
        lines = f.readlines()
        i = 0
        for l in lines :
            s = l.split("\t")
            uid = int(s[0])
            id  = int(s[1])
            ret = cli.eval(iid, uid, id).value
            ret = 1 + (ret) * 4
            real = float(s[2])
            error += (ret - real) ** 2
            i += 1
            cli.train_stream(iid, uid, id, ((real - 1) / 4) * 2 - 1)
            print(f"{i / 200:.2f}%\t{ret:.2f} - {real:.2f}\t{math.sqrt(error/i):.4f}\n", end=LINE_ERASE)
    print(f"RMSE = {math.sqrt(error/i)}")
    total = (time.time() - start)/i * 1000