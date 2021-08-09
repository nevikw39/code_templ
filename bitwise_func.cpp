template <typename T = int64_t>
T inline bwabs(T x)
{
    return (x ^ (x >> ((sizeof(T) << 3) - 1))) - (x >> ((sizeof(T) << 3) - 1));
}
template <typename T = int64_t>
T inline bwmin(T x, T y)
{
    return y ^ ((x ^ y) & -(x < y));
}
template <typename T = int64_t>
T inline bwmax(T x, T y)
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
