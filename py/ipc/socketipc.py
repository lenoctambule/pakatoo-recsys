import socket
from messages import *

class   IPCClient:
    def __init__(self, ip : str = "127.0.0.1", port : int = 4560) -> None:
        self.ip = ip
        self.port = port

    def send_msg(self, msg : Message) -> None :
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s :
            s.connect(self.ip, self.port)
            s.send(msg.build_msg())