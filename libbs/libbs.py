import ctypes
import os

libbs_path = os.path.abspath('libbs/bs.so')  # Adjust path if needed
libbs = ctypes.CDLL(libbs_path)

class Url(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("suffix", ctypes.c_char_p)]

class BSentries(ctypes.Structure):
    _fields_ = [("suffix", ctypes.c_char_p),
                ("names", ctypes.POINTER(ctypes.POINTER(ctypes.c_char_p))),
                ("namelen", ctypes.c_size_t),
                ("n_names", ctypes.c_size_t)]

libbs.create_url.argtypes = [ctypes.c_char_p]
libbs.create_url.restype = Url

libbs.generate_entries.argtypes = [Url, ctypes.c_size_t]
libbs.generate_entries.restype = BSentries

libbs.bitsquat_entries.argtypes = [BSentries, ctypes.c_int]
libbs.print_bs_entries.argtypes = [BSentries]

libbs.free_url.argtypes = [Url]
libbs.free_bs_entries.argtypes = [BSentries]

def create_entries(url_input: str, n_entries: int, n_flips: int):
    url_bytes = url_input.encode('utf-8')
    url = libbs.create_url(url_bytes)
    if not url.name or not url.suffix:
        raise ValueError(f"Invalid URL: {url_input}")
    bs_entries = libbs.generate_entries(url, n_entries)
    libbs.bitsquat_entries(bs_entries, n_flips)
    suffix = bs_entries.suffix.decode('utf-8') if bs_entries.suffix else "No suffix"
    generated_names = []
    for i in range(bs_entries.n_names):
        entry_name = bs_entries.names[i]
        full_entry = f"{ctypes.cast(entry_name, ctypes.c_char_p).value.decode('utf-8')}.{suffix}"
        generated_names.append(full_entry)
    libbs.free_bs_entries(bs_entries)
    libbs.free_url(url)
    return generated_names
