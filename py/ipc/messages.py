import ctypes

class   Message:
    def __init__(self,
                 instance_id : ctypes.c_ushort,
                 cmd_id : ctypes.c_ushort,
                 msg : bytes,
                 ) -> None:
        self.instance_id    = ctypes.c_ushort(instance_id)
        self.cmd_id         = ctypes.c_ushort(cmd_id)
        self.msg            = msg 
        self.message_len    = ctypes.c_ulong(len(msg))

    def build_msg(self):
        b_cmd_id     = ctypes.cast(ctypes.byref(self.cmd_id), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(self.cmd_id)))
        b_msg_len    = ctypes.cast(ctypes.byref(self.message_len), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(self.message_len)))
        b_inst_id    = ctypes.cast(ctypes.byref(self.instance_id), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(self.instance_id)))
        return b_inst_id.contents.raw + b_cmd_id.contents.raw + b_msg_len.contents.raw + self.msg