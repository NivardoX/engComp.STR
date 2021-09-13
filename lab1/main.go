package main

import (
	"fmt"
	"sync"
)

var cycleSize = 3
var outputSize = 30
var output []rune

func fillCharSlice(offset int) {
	for i := offset - 1; i < outputSize; i=i+ cycleSize {
		output[i] = rune(offset+64)
	}}

func main() {

	var wg sync.WaitGroup
	output = make([]rune,outputSize)

	for i := 1; i <= cycleSize; i++ {
		wg.Add(1)
		i := i
		go func() {
			defer wg.Done()
			fillCharSlice(i)
		}()

	}

	wg.Wait()
	fmt.Printf(string(output))
}