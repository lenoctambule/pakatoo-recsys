import socket
import ctypes
from messages import *

class   IPCClient:
    def __init__(self, ip : str = "127.0.0.1", port : int = 4560) -> None:
        self.ip = ip
        self.port = port

    def send_msg(self, msg : Message) -> bytes :
        r = b""
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s :
            s.connect((self.ip, self.port))
            s.send(msg.get_msg())
            r += s.recv(50)
        return r
    
    def create_instance(self) -> ctypes.c_ulong:
        r = self.send_msg(CreateInstanceMessage())[9:]
        iid = ctypes.c_ulong()
        ctypes.memmove(ctypes.pointer(iid), r, ctypes.sizeof(iid))
        return iid

    def train_stream(self, iid, uid, id, val):
        self.send_msg(TrainStreamMessage(iid, uid, id, val))

    def eval(self, iid, uid, id) -> ctypes.c_float:
        r = self.send_msg(EvalMessage(iid, uid, id))[9:]
        eval = ctypes.c_float()
        ctypes.memmove(ctypes.pointer(eval), r, ctypes.sizeof(eval))
        return eval
