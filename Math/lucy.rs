fn isqrt(n: u64) -> u32 {
    if n <= 1 {
        return n as u32;
    }
    let z: u64 = n >> 2;
    let r2: u32 = 2 * isqrt(z);
    let r3: u32 = r2 + 1;
    if n < r3 as u64 * r3 as u64 {
        return r2;
    } else {
        return r3;
    }
}

fn prime_sieve(n: u32) -> Vec<u32> {
    let mut is_prime = vec![true; n as usize];
    let mut primes: Vec<u32> = Vec::new();

    for i in 2..n {
        if is_prime[i as usize] {
            primes.push(i);
            let mut j: u64 = i as u64 * i as u64;
            while j < n as u64 {
                is_prime[j as usize] = false;
                j += i as u64;
            }
        }
    }

    primes
}

fn g(n: u64, prime_index: i32, primes: &[u32]) -> u64 {
    if prime_index == -1 {
        return (n * (n + 1)) / 2 - 1;
    }
    let prime: u32 = primes[prime_index as usize];
    if prime as u64 * prime as u64 >= n {
        return g(n, prime_index - 1, primes);
    }
    g(n, prime_index - 1, primes)
        - prime as u64
            * (g(n / prime as u64, prime_index - 1, primes)
                - g(prime as u64 - 1, prime_index - 1, primes));
}

fn find_prime_number(n: u32, primes: &[u32]) -> usize {
    let mut lo = 0;
    let mut hi = primes.len();

    while lo < hi {
        let me = lo + (hi - lo + 1) / 2;
        if primes[me] <= n {
            lo = me;
        } else {
            hi = me - 1;
        }
    }
    if primes[lo] > n && lo > 0 {
        lo -= 1;
    }
    lo
}

fn lucy_recursive(n: u64, primes: &[u32]) -> u64 {
    let n_sqrt: u32 = isqrt(n);
    let prime_index: usize = find_prime_number(n_sqrt, primes);
    g(n, prime_index as i32, primes)
}

/* Iterative approach */

struct FloorIndexedArray {
    number: u64,
    n_sqrt: u32,
    size: usize,
    array: Vec<u64>,
}

impl FloorIndexedArray {
    fn new(n: u64) -> Self {
        let n_sqrt: u32 = isqrt(n);
        let mut array: Vec<u64> = (1..=n_sqrt as u64).collect::<Vec<_>>();
        for i in (1..=n_sqrt).rev() {
            if n / i as u64 == i as u64 {
                continue;
            }
            array.push(n / i as u64);
        }
        Self {
            number: n,
            n_sqrt,
            size: array.len(),
            array,
        }
    }

    fn get_index(&self, x: u64) -> usize {
        if x <= self.n_sqrt as u64 {
            (x - 1) as usize
        } else {
            let offset: u64 = 2 * self.n_sqrt as u64
                - (if self.number / self.n_sqrt as u64 == self.n_sqrt as u64 {
                    1u64
                } else {
                    0u64
                });
            (offset - self.number / x) as usize
        }
    }
}

fn lucy(n: u64, primes: &[u32]) -> u64 {
    let n_sqrt: u32 = isqrt(n);
    let prime_index: usize = find_prime_number(n_sqrt, primes);
    let floor_indexed_array = FloorIndexedArray::new(n);
    let mut s = vec![0u64; floor_indexed_array.size];

    for (i, &v) in floor_indexed_array.array.iter().enumerate() {
        s[i] = (v * (v + 1)) / 2 - 1;
    }

    for i in 0..=prime_index {
        let prime: u32 = primes[i];
        for j in (0..floor_indexed_array.size).rev() {
            let v: u64 = floor_indexed_array.array[j];
            if v < prime as u64 * prime as u64 {
                break;
            }
            let previous_prime: u32 = if i > 0 { primes[i - 1] } else { 1u32 };
            let pos: usize = floor_indexed_array.get_index(v / prime as u64);
            let previous_prime_pos: usize = floor_indexed_array.get_index(previous_prime as u64);
            s[j] -= prime as u64 * (s[pos] - s[previous_prime_pos]);
        }
    }
    s[s.len() - 1]
}

fn main() {
    let n: u64 = 100_000_000_000;
    let primes = prime_sieve(10_000_000);
    println!("{}", lucy(n, &primes));
}
