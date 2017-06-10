from _true import lib

"""
Function for returning True, implemented in C for performance reasons.
"""
def get_true():
    return bool(lib.get_true())
