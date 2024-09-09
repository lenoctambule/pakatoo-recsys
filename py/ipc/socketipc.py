import socket
import ctypes
from messages import *

BUFFER_SIZE=3

class Response:
    code            = 0
    len             = 0
    raw             = bytes()
    is_finished     = False
    parsed_header   = False

    def get_body(self):
        return self.raw[9:]

class   IPCClient:
    def __init__(self, ip : str = "127.0.0.1", port : int = 4560) -> None:
        self.ip = ip
        self.port = port

    def recv_msg(self, s : socket.socket):
        r = Response()
        while (r.is_finished == False) :
            r.raw += s.recv(BUFFER_SIZE)
            if len(r.raw) >= 9 and r.parsed_header == False:
                r.parsed_header = True
                len_tmp         = ctypes.c_ulong()
                ctypes.memmove(ctypes.pointer(len_tmp), r.raw[1:9], ctypes.sizeof(len_tmp))
                r.len           = len_tmp.value
                r.code          = r.raw[0]
            if (len(r.raw) >= r.len + 9 and r.parsed_header == True):
                r.is_finished = True
        return r

    def send_msg(self, msg : Message) -> Response :
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s :
            s.connect((self.ip, self.port))
            s.send(msg.get_msg())
            r = self.recv_msg(s)
        return r
    
    def create_instance(self) -> ctypes.c_ulong:
        r    = self.send_msg(CreateInstanceMessage()).get_body()
        iid = ctypes.c_ulong()
        ctypes.memmove(ctypes.pointer(iid), r, ctypes.sizeof(iid))
        return iid

    def train_stream(self, iid, uid, id, val):
        self.send_msg(TrainStreamMessage(iid, uid, id, val))

    def eval(self, iid, uid, id) -> ctypes.c_float:
        r = self.send_msg(EvalMessage(iid, uid, id)).get_body()
        eval = ctypes.c_float()
        ctypes.memmove(ctypes.pointer(eval), r, ctypes.sizeof(eval))
        return eval
