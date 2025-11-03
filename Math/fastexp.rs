fn fastexp(u128 x, u128 y, u128 p) -> u128 {
    let mut power: u128 = 1;
    while y > 0 {
        if y&1 != 0 {
            ans *= x;
            ans %= p;
        }
        y >>= 1;
        x *= x;
        x %= p;
    }
    ans%p
}

fn inverse_modular(u128 x, u128 p) -> u128 {
    fastexp(x, p-2, p)
}
