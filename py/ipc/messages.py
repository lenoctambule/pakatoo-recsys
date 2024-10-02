import ctypes
import utils

def serialize_ctype(obj):
    return ctypes.cast(ctypes.byref(obj), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(obj))).contents.raw

def serialize_args(l : list) -> bytes :
    ret = b""
    for e in l :
        ret += serialize_ctype(e)
    return ret

class   Message:
    def __init__(self,
                 instance_id : int,
                 cmd_id : int,
                 msg : bytes,
                 ) -> None:
        self.inst_id    = ctypes.c_ushort(instance_id)
        self.cmd_id     = ctypes.c_ushort(cmd_id)
        self.msg        = msg
        self.msg_len    = ctypes.c_ulong(len(msg))

    def get_msg(self):
        b_cmd_id     = serialize_ctype(self.cmd_id)
        b_msg_len    = serialize_ctype(self.msg_len)
        b_inst_id    = serialize_ctype(self.inst_id)
        b_msg        = b_inst_id + b_cmd_id + b_msg_len + self.msg
        return b_msg

class   CreateInstanceMessage(Message):
    def __init__(self) -> None:
        msg = bytes()
        msg += b"create_instance"
        super().__init__(0, 1, msg)

class   StreamTrainMessage(Message):
    def __init__(self, 
                 instance_id : int,
                 uid: int,
                 id : int,
                 val : float) -> None:
        msg             = bytes()
        msg             += serialize_args([ctypes.c_ulong(uid),
                                          ctypes.c_ulong(id),
                                          ctypes.c_float(val),])
        super().__init__(instance_id, 2, msg)

class   StreamDeleteMessage(Message):
    def __init__(self, 
                 instance_id : int,
                 uid: int) -> None:
        msg             = bytes()
        msg             += serialize_args([ctypes.c_ulong(uid),])
        super().__init__(instance_id, 3, msg)

class   StreamInitMessage(Message):
    def __init__(self, 
                 instance_id : int,
                 uid: int,
                 history: list) -> None:
        msg             = bytes()
        args            = [ctypes.c_ulong(uid),]
        args.extend(history)
        msg             += serialize_args(args)
        super().__init__(instance_id, 4, msg)

class   EvalMessage(Message):
    def __init__(self, 
                 instance_id: int,
                 uid: int,
                 id : int) -> None:
        msg         = bytes()
        msg         += serialize_args([ctypes.c_ulong(uid), ctypes.c_ulong(id)])
        super().__init__(instance_id, 5, msg)

class   SaveInstanceMessage(Message):
    def __init__(self) -> None:
        msg = bytes()
        msg += b"save_instance"
        super().__init__(0, 6, msg)

class   PingMessage(Message):
    def __init__(self) -> None:
        msg = bytes()
        msg += b"Ping"
        super().__init__(0, 0, msg)