from cffi import FFI
ffi = FFI()

_LIBTRUE_CDEF = '''
bool get_true(void);
'''
_SRC_PATH = '../libtrue/true.c'
ffi.set_source('true._true',
               open(_SRC_PATH).read(),
               extra_compile_args=['-Wall', '-Wextra', '-Werror',
                                   '-I../libtrue/'])
ffi.cdef(_LIBTRUE_CDEF)

if __name__ == '__main__':
    ffi.compile(verbose=True)
