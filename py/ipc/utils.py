import ctypes

class   t_clamped(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_ulong),
        ("val", ctypes.c_float)
    ]

    def serialize(self) -> bytes:
        return ctypes.cast(ctypes.byref(self), ctypes.POINTER(ctypes.c_char * ctypes.sizeof(self)))

def serialize_clamped_list(l : list) -> bytes :
    res = bytes()
    for i in l :
        res += i.serialize()
    return res