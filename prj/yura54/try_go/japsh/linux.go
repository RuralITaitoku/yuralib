//go:build linux
package main

/*
#include "native/native.h"
#include "native/linux.c"
*/
import "C"

func getch_with_timeout() {

    C.getch_with_timeout(C.int(10))
}

