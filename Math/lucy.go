package main

import "fmt"

const sieveLimit int32 = 1000000

func primeSieve(n int32) (isPrime []bool, primes []int32) {
	isPrime = make([]bool, n, n)
	for i, _ := range isPrime {
		isPrime[i] = true
	}
	isPrime[0], isPrime[1] = false, false

	primes = make([]int32, 0, 0)
	for i := int32(2); i < n; i++ {
		if isPrime[i] {
			primes = append(primes, i)
			for j := int64(i) * int64(i); j < int64(n); j += int64(i) {
				isPrime[j] = false
			}
		}
	}
	return
}

func iSqrt(n int64) int32 {
	if n <= 1 {
		return int32(n)
	}

	var z int64 = n >> 2
	var r2 int32 = 2 * iSqrt(z)
	var r3 int32 = r2 + 1

	if n < int64(r3)*int64(r3) {
		return r2
	} else {
		return r3
	}
}

func primePi(n int32, primes []int32) int32 {
	var left int32 = 0
	var right int32 = int32(len(primes)) - 1
	for left < right {
		var middle int32 = left + (right-left+1)/2
		if primes[middle] <= n {
			left = middle
		} else {
			right = middle - 1
		}
	}
	if primes[left] > n {
		left--
	}
	return left + 1
}

func g(n int64, primeIndex int32, primes []int32) int64 {
	if primeIndex == -1 {
		return n*(n+1)/2 - 1
	}
	var prime int64 = int64(primes[primeIndex])
	var s int64 = g(n, primeIndex-1, primes)
	if prime*prime <= n {
		s -= prime * (g(n/prime, primeIndex-1, primes) - g(prime-1, primeIndex-1, primes))
	}
	return s
}

func lucyRecursive(n int64, primes []int32) int64 {
	var nSqrt int32 = iSqrt(n)
	var primeIndex int32 = primePi(nSqrt, primes) - 1
	return g(n, primeIndex, primes)
}

func main() {
	var _, primes = primeSieve(sieveLimit)

	var n int64
	fmt.Scanf("%d", &n)
	fmt.Println(lucyRecursive(n, primes))
}
