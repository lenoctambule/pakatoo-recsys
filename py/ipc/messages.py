import ctypes
import utils

def serialize_ctype(obj):
    return ctypes.cast(ctypes.byref(obj), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(obj))).contents.raw

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
        b_msg        = b_inst_id + b_cmd_id + b_msg_len + self.msg
        return b_msg

class   CreateInstanceMessage(Message):
    def __init__(self) -> None:
        msg = bytes()
        msg += b"created_instance"
        super().__init__(0, 1, msg)

class   TrainStreamMessage(Message):
    def __init__(self, 
                 instance_id : int,
                 uid: ctypes.c_ulong,
                 id : utils.t_clamped,
                 val) -> None:
        msg             = bytes()
        self.uid        = ctypes.c_ulong(uid)
        self.id         = ctypes.c_ulong(id)
        self.val        = ctypes.c_float(val)
        b_uid           = serialize_ctype(self.uid)
        b_clamped_id    = serialize_ctype(self.id)
        b_clamped_val   = serialize_ctype(self.val)
        msg         += b_uid + b_clamped_id + b_clamped_val
        super().__init__(instance_id, 2, msg)

class   EvalMessage(Message):
    def __init__(self, 
                 instance_id: ctypes.c_ushort,
                 uid: ctypes.c_ulong,
                 id : ctypes.c_ulong) -> None:
        msg         = bytes()
        self.uid    = ctypes.c_ulong(uid)
        self.id     = ctypes.c_ulong(id)
        msg         += serialize_ctype(self.uid) + serialize_ctype(self.id)
        super().__init__(instance_id, 5, msg)
