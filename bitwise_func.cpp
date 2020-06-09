template <typename T = int64_t>
T inline myabs(T x)
{
    return (x ^ (x >> ((1 << sizeof(T)) - 1))) - (x >> ((1 << sizeof(T)) - 1));
}
template <typename T = int64_t>
T inline mymin(T x, T y)
{
    return y ^ ((x ^ y) & -(x < y));
}
template <typename T = int64_t>
T inline mymax(T x, T y)
{
    return x ^ ((x ^ y) & -(x < y));
}
template <typename T = int64_t>
bool inline ispow2(T x)
{
    return !(x & (x - 1));
}
template <typename T = int64_t>
T inline rev(T x)
{
    return ~x + 1;
}