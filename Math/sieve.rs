fn sieve(n: u32) -> Vec<u32> {
    let mut is_prime: Vec<bool> = vec![true; n as usize];
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

fn build_lpf(n: u32) -> Vec<u32> {
    let mut lpf: Vec<u32> = vec![0; n as usize];
    for i in 2..n {
        if lpf[i as usize] == 0 {
            lpf[i as usize] = i;
            let mut j: u64 = i as u64 * i as u64;
            while j < n as u64 {
                if lpf[j as usize] == 0 {
                    lpf[j as usize] = i;
                }
                j += i as u64;
            }
        }
    }
    lpf
}

fn build_phi(n: u32) -> Vec<u32> {
    let mut phi: Vec<u32> = vec![0; n as usize];
    for i in 2..n {
        if phi[i as usize] == 0 {
            phi[i as usize] = i - 1;
            let mut j: u32 = 2 * i;
            while j < n {
                if phi[j as usize] == 0 {
                    phi[j as usize] = j;
                }
                phi[j as usize] /= i;
                phi[j as usize] *= i - 1;
                j += i;
            }
        }
    }
    phi
}
