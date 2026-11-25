//go:build linux
package main

/*
#include "native/native.h"
#include "native/linux.c"
*/
import "C"

func getch_with_timeout(timeout int) int {

    ch := C.getch_with_timeout(C.int(timeout))
    return int(ch);
}

