import matplotlib.pyplot as plt
import ctypes
import numpy

def display_mat(path : str, size : int):
    mat = numpy.zeros((size,size), dtype=float)
    with open(path, "rb") as f :
        f.read(12)
        n_tokens = ctypes.c_ulong()
        ctypes.memmove(ctypes.pointer(n_tokens), f.read(8), ctypes.sizeof(n_tokens))
        print(n_tokens.value)
        for i in range(n_tokens.value):
            self_id = ctypes.c_ulong()
            adj_len = ctypes.c_ulong()
            ctypes.memmove(ctypes.pointer(self_id), f.read(8), ctypes.sizeof(self_id))
            ctypes.memmove(ctypes.pointer(adj_len), f.read(8), ctypes.sizeof(adj_len))
            for j in range(adj_len.value):
                target_id = ctypes.c_ulong()
                ctypes.memmove(ctypes.pointer(target_id), f.read(8), ctypes.sizeof(target_id))
                weight    = ctypes.c_float()
                ctypes.memmove(ctypes.pointer(weight), f.read(4), ctypes.sizeof(target_id))
                mat[target_id.value - 1, self_id.value - 1] = weight.value
                mat[self_id.value - 1, target_id.value - 1] = weight.value
    plt.matshow(mat)
    plt.show()