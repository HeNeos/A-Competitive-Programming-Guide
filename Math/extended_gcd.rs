fn extended_gcd(u128 a, u128 b) -> (u128, u128, u128) {
    let mut (old_r, r): (u128, u128) = (a, b);
    let mut (old_s, s): (u128, u128) = (1, 0);
    let mut (old_t, t): (u128, u128) = (0, 1);
    while r != 0 {
        let mut q = old_r / r;
        (old_r, r) = (r, old_r - q*r);
        (old_s, s) = (s, old_s - q*s);
        (old_t, t) = (t, old_t - q*t);
    }
    (old_r, old_s, old_t)
}
