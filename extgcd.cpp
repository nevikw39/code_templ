template<typename T = int64_t>
T extgcd(T a, T b, T &x, T &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    T g = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}