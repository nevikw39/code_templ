template <typename T = int64_t>
T mulmod(T a, T b, T m)
{
    T y = 0;
    for (a %= m; b; b >>= 1, a = (a << 1) % m)
        if (b & 1)
            y = (y + a) % m;
    return y;
}
template <typename T = int64_t>
T binpow(T a, T n, T m)
{
    T y = 1;
    for (a %= m; n; n >>= 1, a = mulmod(a, a, m))
        if (n & 1)
            y = mulmod(y, a, m);
    return y;
}
