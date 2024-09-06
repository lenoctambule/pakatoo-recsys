from socketipc import *
import unittest

if __name__ == "__main__" :
    msg = Message(0, 0, b"salut ca va")
    cli = IPCClient()
    print(cli.send_msg(msg))