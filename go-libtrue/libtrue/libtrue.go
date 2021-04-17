package libtrue

// #cgo CFLAGS: -g -Wall -I/usr/include
// #cgo LDFLAGS: -L/usr/lib -ltrue
// #include <stdbool.h>
// #include <true.h>
// bool get_true(void);
import "C"

// GetTrue function returns true implemented in C for performance reasons.
func GetTrue() C.bool {
	return C.bool(C.get_true())
}
