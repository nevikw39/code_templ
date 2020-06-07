struct disjoint_set
{
    int n;
    vector<int> p, r;
    disjoint_set(int _n) : n(_n + 1)
    {
        r = vector<int>(n);
        for (int i = 0; i < n;)
            p.push_back(i++);
    }
    int find(int x)
    {
        if (x >= n)
            return -1;
        if (p[x] == x)
            return x;
        return p[x] = find(p[x]);
    }
    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (r[x] < r[y])
            p[x] = y;
        else
        {
            p[y] = x;
            r[x] += r[x] == r[y];
        }
    }
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};