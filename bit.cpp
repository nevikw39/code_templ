struct bit
{
    vector<int> v;
    bit(int n)
    {
        v.resize(n + 1);
    }
    int inline lowbit(int x)
    {
        return x & -x;
    }
    void update(int x, int val = 1)
    {
        for (int i = x, n = v.size(); i < n; i += lowbit(i))
            v[i] += val;
    }
    int query(int x)
    {
        int y = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            y += v[i];
        return y;
    }
};
struct bit2d
{
    int n;
    vector<bit> v;
    bit2d(int _n) : n(_n)
    {
        v.resize(n + 1, bit(n));
    }
    int inline lowbit(int x)
    {
        return x & -x;
    }
    int query(int x, int y)
    {
        int z = 0;
        for (; x; x -= lowbit(x))
            z += v[x].query(y);
        return z;
    }
    void update(int x, int y, int val = 1)
    {
        for (; x <= n; x += lowbit(x))
            v[x].update(y, val);
    }
};
struct bit_lis
{
    int n;
    vector<int> v;
    bit_lis(int _n): n(_n)
    {
        v.resize(n + 1);
    }
    int inline lowbit(int x)
    {
        return x & -x;
    }
    int query(int x)
    {
        int y = 0;
        for (; x; x -= lowbit(x))
            y = max(y, v[x]);
        return y;
    }
    void update(int x)
    {
        int val = query(x - 1) + 1;
        for (; x <= n; x += lowbit(x))
            v[x] = max(v[x], val);
    }
};