template <typename T = int64_t>
struct st_min
{
    bool operator()(const T &l, const T &r) const
    {
        return l < r ? l : r;
    }
};
template <typename T = int64_t>
struct st_max
{
    bool operator()(const T &l, const T &r) const
    {
        return l > r ? l : r;
    }
};
template <typename T = int64_t>
struct st_sum
{
    bool operator()(const T &l, const T &r) const
    {
        return l + r;
    }
};
template <typename T = int64_t, int N = 1000000, typename func = st_min<T>>
struct seg_tree
{
    T a[N + 1], d[N << 1 | 1];
    void build(T l, T r, T p)
    {
        if (l == r)
        {
            d[p] = a[l];
            return;
        }
        T m = (l + r) >> 1;
        build(l, m, p << 1);
        build(m + 1, r, (p << 1) | 1);
        d[p] = func(d[p << 1], d[(p << 1) | 1]);
    }
    T query(T l, T r, T s, T t, T p)
    {
        if (l > t || r < s)
            return -1;
        if (l <= s && t <= r)
            return d[p];
        T m = (s + t) >> 1;
        return func(query(l, r, s, m, p << 1), query(l, r, m + 1, t, (p << 1) | 1));
    }
};