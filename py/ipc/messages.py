import ctypes
import utils

def serialize_ctype(obj):
    return ctypes.cast(ctypes.byref(obj), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(obj)))

class   Message:
    def __init__(self,
                 instance_id : ctypes.c_ushort,
                 cmd_id : ctypes.c_ushort,
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
        return b_inst_id.contents.raw + b_cmd_id.contents.raw + b_msg_len.contents.raw + self.msg

class   CreateInstanceMessage(Message):
    def __init__(self, 
                 instance_id: ctypes.c_ushort,
                 cmd_id: ctypes.c_ushort) -> None:
        msg = bytes()
        super().__init__(instance_id, cmd_id, msg)

class   TrainStreamMessage(Message):
    def __init__(self, 
                 instance_id: ctypes.c_ushort,
                 cmd_id: ctypes.c_ushort,
                 uid: ctypes.c_ulong,
                 clamped : utils.t_clamped) -> None:
        msg         = bytes()
        self.uid    = ctypes.c_ulong(uid)
        msg         += serialize_ctype(self.uid) + serialize_ctype(clamped)
        super().__init__(instance_id, cmd_id, msg)

class   EvalMessage(Message):
    def __init__(self, 
                 instance_id: ctypes.c_ushort,
                 cmd_id: ctypes.c_ushort,
                 uid: ctypes.c_ulong,
                 id : ctypes.c_ulong) -> None:
        msg         = bytes()
        self.uid    = ctypes.c_ulong(uid)
        msg         += serialize_ctype(self.uid) + serialize_ctype(id)
        super().__init__(instance_id, cmd_id, msg)
