struct disjoint_set
{
    int n, g;
    vector<int> p, r;
    disjoint_set(int _n) : n(_n + 1)
    {
        g = n;
        r = vector<int>(n, 1);
        for (int i = 0; i < n;)
            p.push_back(i++);
    }
    int find(int x)
    {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        --g;
        if (r[x] < r[y])
        {
            p[x] = y;
            r[y] += r[x];
        }
        else
        {
            p[y] = x;
            r[x] += r[y];
        }
        return true;
    }
    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};