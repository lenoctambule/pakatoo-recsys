import socket
from messages import *

class   IPCClient:
    def __init__(self, ip : str = "127.0.0.1", port : int = 4560) -> None:
        self.ip = ip
        self.port = port

    def send_msg(self, msg : Message) -> bytes :
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s :
            s.connect((self.ip, self.port))
            s.send(msg.get_msg())
            r = s.recv()

    def train_stream(self, iid, uid, clamped):
        self.send_msg(TrainStreamMessage(iid, 0, uid, clamped))

    def eval(self, iid, uid, id) -> ctypes.c_float:
        self.send_msg(EvalMessage(iid, 1, uid, id))