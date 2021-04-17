package main

import (
	"fmt"
	"libtrue"
)

func main() {
	ret := libtrue.GetTrue()
	fmt.Printf("%T\n", ret)
	fmt.Println(ret)
}
