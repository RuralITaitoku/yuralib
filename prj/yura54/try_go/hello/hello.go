package main

import (
    "fmt"
    "RuralITaitoku/greetings"
)

func main() {
    message := greetings.Hello("Gladys")
    fmt.Println(message)
}
