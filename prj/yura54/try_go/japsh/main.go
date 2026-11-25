package main

import (
        "log"
       )
func main() {
    log.Println("log")
    for {
        ch := getch_with_timeout(999)
        log.Printf("%d", ch)
        if ch == 113 {
            break
        }
    }
}
