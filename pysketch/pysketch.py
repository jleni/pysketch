# Distributed under the MIT software license, see the accompanying
# file LICENSE or http://www.opensource.org/licenses/mit-license.php.

from ctypes import *
import numpy as np
from numpy.ctypeslib import as_ctypes
import os

sketch_lib = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__), 'libpysketch.so'))

sketch_lib.Sketch_new.argtypes = [c_int, c_int]
sketch_lib.Sketch_new.restype = c_void_p
sketch_lib.Sketch_delete.argtypes = [c_void_p]
sketch_lib.Sketch_delete.restype = None

sketch_lib.Sketch_get_hash.argtypes = [c_void_p, c_void_p, c_size_t]
sketch_lib.Sketch_get_hash.restype = c_ulonglong
sketch_lib.Sketch_get_hash_incremental.argtypes = [c_void_p, c_ulonglong, c_void_p, c_size_t]
sketch_lib.Sketch_get_hash_incremental.restype = c_ulonglong

sketch_lib.Sketch_get_column_indexes.argtypes = [c_void_p, c_ulonglong, c_void_p]
sketch_lib.Sketch_get_column_indexes.restype = None

sketch_lib.Sketch_increment.argtypes = [c_void_p, c_ulonglong]
sketch_lib.Sketch_increment.restype = None
sketch_lib.Sketch_query.argtypes = [c_void_p, c_ulonglong]
sketch_lib.Sketch_query.restype = c_ulonglong

sketch_lib.Sketch_increment_idxs.argtypes = [c_void_p, c_void_p]
sketch_lib.Sketch_increment_idxs.restype = None
sketch_lib.Sketch_query_idxs.argtypes = [c_void_p, c_void_p]
sketch_lib.Sketch_query_idxs.restype = c_ulonglong

class pySketch(object):
    def __init__(self):
        self.sketch_obj = sketch_lib.Sketch_new(10, 10)

    def __del__(self):
        sketch_lib.Sketch_delete(self.sketch_obj)

    def get_hash(self, data):
        # Assumes that data is a numpy array, dtype=uint8
        return sketch_lib.Sketch_get_hash(self.sketch_obj, as_ctypes(data), data.size)

    def get_hash_incremental(self, prev_hash, data):
        # Assumes that data is a numpy array, dtype=uint8
        return sketch_lib.Sketch_get_hash(self.sketch_obj, prev_hash, as_ctypes(data), data.size)

    def get_column_indexes(self, hash, indexes):
        # TODO: get d and check that indexes is the right size
        sketch_lib.Sketch_get_column_indexes(self.sketch_obj, hash, as_ctypes(indexes))

    def increment(self, hash):
        sketch_lib.Sketch_increment(self.sketch_obj, hash)

    def query(self, hash):
        return sketch_lib.Sketch_query(self.sketch_obj, hash)

    def increment_idxs(self, indexes):
        sketch_lib.Sketch_increment_idxs(self.sketch_obj, indexes)

    def query_idxs(self, indexes):
        return sketch_lib.Sketch_query_idxs(self.sketch_obj, indexes)
