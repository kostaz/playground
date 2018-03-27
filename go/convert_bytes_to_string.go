package main

import "fmt"

func main() {
	bytes := []byte{0xaf, 0xb7, 0x4f, 0x56}
	str := hex.EncodeToString(bytes)

	fmt.Printf("%x\n", bytes) // afb74f56
	fmt.Printf("%s\n", str)   // afb74f56
}
