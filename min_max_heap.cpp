class min_max_heap
{
private:
    vector<int> v;           // base container
    void trickle_down(int x) // the helper function used when poped
    {
        bool is_min = ~__lg(x + 1) & 1;
        while (x + 1 << 1 <= v.size())
        {
            int m = get(x, is_min);
            if (is_min ? v[m] < v[x] : v[m] > v[x])
            {
                swap(v[m], v[x]);
                if (m <= x + 1 << 1)
                    return;
                if (is_min ? v[(m + 1 >> 1) - 1] < v[m] : v[(m + 1 >> 1) - 1] > v[m])
                    swap(v[(m + 1 >> 1) - 1], v[m]);
                x = m;
            }
            else
                return;
        }
    }
    int get(int x, bool is_min) // get the descendent of `x`
    {
        int y = (++x << 1) - 1;
        for (int i = 2; i <= 4; i <<= 1)
            for (int j = 0; j < i; j++)
            {
                int tmp = x * i + j - 1;
                if (tmp >= v.size())
                    return y;
                if (is_min ? v[y] > v[tmp] : v[y] < v[tmp])
                    y = tmp;
            }
        return y;
    }
    void bubble_up(int x) // the helper function used when pushed
    {
        if (!x)
            return;
        int p = (x + 1 >> 1) - 1;
        bool is_min = ~__lg(x + 1) & 1;
        if (is_min ? v[p] < v[x] : v[p] > v[x])
        {
            swap(v[p], v[x]);
            bubble_up(p, !is_min);
        }
        else
            bubble_up(x, is_min);
    }
    void bubble_up(int x, bool is_min) // the helper function used when pushed
    {
        while (x > 2)
        {
            int gp = (x + 1 >> 2) - 1;
            if (is_min ? v[x] < v[gp] : v[x] > v[gp])
            {
                swap(v[x], v[gp]);
                x = gp;
            }
            else
                break;
        }
    }
    int find_max() const // return the index of the maximum element
    {
        int y = 0;
        for (int i = min(2, int(v.size()) - 1); i; i--)
            if (v[y] < v[i])
                y = i;
        return y;
    }
    void erase(int x) // erase the element whose index is `x`
    {
        v[x] = v.back();
        v.pop_back();
        trickle_down(x);
    }

public:
    inline bool empty() const { return v.empty(); } // determine whether the depq is empty
    inline int size() const { return v.size(); }    // return the size of depq
    void push(int x)                                // push the element into depqF
    {
        v.push_back(x);
        bubble_up(size() - 1);
    }
    inline int front() const { return v.front(); }    // return the minimum element
    inline int back() const { return v[find_max()]; } // return the maximum element
    inline void pop_front() { erase(0); }             // pop the minimum element
    inline void pop_back() { erase(find_max()); }     // pop the maximum element
};
