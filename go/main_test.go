package main

import (
	"sync"
	"testing"
	"time"
)

func TestSum(t *testing.T) {
	var mtx sync.Mutex
	sum := 0
	for i := 0; i < 100; i++ {
		i := i

		go func() {
			mtx.Lock()
			sum = sum + i
			mtx.Unlock()
		}()
	}
	time.Sleep(1 * time.Second)
	if sum != 4950 {
		t.Errorf("sum = %d", sum)
	}
}

// go test main_test.go
