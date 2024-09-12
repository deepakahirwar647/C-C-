import ctypes


class Vector_c(ctypes.Structure):
    _fields_ = [("size", ctypes.c_size_t),
                ("arr", ctypes.POINTER(ctypes.c_double))]


class Vector:
    def __init__(self, arr: Vector_c):
        self.arr: Vector_c = arr

    def __str__(self):
        lib.print_vector(self.arr)
        return ""

    def __iter__(self):
        return (lib.get_ve(self.arr, i) for i in range(self.size))

    @property
    def size(self):
        try:
            return self.arr.contents.size
        except AttributeError:
            return 0

    def __getitem__(self, index):
        index = index if index >= 0 else self.size + index
        if index >= self.size:
            raise IndexError(f"Index {index} out of range")
        return lib.get_ve(self.arr, index)

    def __del__(self):
        if self.arr is not None:
            lib.free_vector(self.arr)


lib = ctypes.CDLL("./vector.so")

lib.empty_like.argtypes = [ctypes.POINTER(Vector_c)]
lib.empty_like.restype = ctypes.POINTER(Vector_c)


def empty_like(v: Vector):
    return Vector(lib.empty_like(v.arr))


lib.empty.argtypes = [ctypes.c_size_t]
lib.empty.restype = ctypes.POINTER(Vector_c)


def empty(n: int):
    return Vector(lib.empty(n))


lib.zeros_like.argtypes = [ctypes.POINTER(Vector_c)]
lib.zeros_like.restype = ctypes.POINTER(Vector_c)


def zeros_like(v: Vector):
    return Vector(lib.zeros_like(v.arr))


lib.zeros.argtypes = [ctypes.c_size_t]
lib.zeros.restype = ctypes.POINTER(Vector_c)


def zeros(n: int):
    return Vector(lib.zeros(n))


lib.arange.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double]
lib.arange.restype = ctypes.POINTER(Vector_c)


def arange(start, stop, step=1):
    return Vector(lib.arange(start, stop, step))


lib.linspace.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_size_t]
lib.linspace.restype = ctypes.POINTER(Vector_c)


def linspace(start, end, n):
    return Vector(lib.linspace(start, end, n))


lib.gradient.argtypes = [ctypes.POINTER(Vector_c), ctypes.POINTER(Vector_c)]
lib.gradient.restype = ctypes.POINTER(Vector_c)

lib.print_vector.argtypes = [ctypes.POINTER(Vector_c)]


lib.get_ve.argtypes = [ctypes.POINTER(Vector_c), ctypes.c_int]
lib.get_ve.restype = ctypes.c_double


v = linspace(1, 4, 19)
for x in v:
    print(x)
print(v[1])
