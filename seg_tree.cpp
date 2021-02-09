template<typename T>
struct st_sum
{
    constexpr static T e = 0;
    inline static T foo(T x, T y)
    {
        return x + y;
    }
    inline static T bar(T x)
    {
        return x;
    }
};
template<typename T>
struct st_min
{
    constexpr static T e = numeric_limits<T>::max();
    inline static T foo(T x, T y)
    {
        return min(x, y);
    }
    constexpr static T bar(T x)
    {
        return 1;
    }
};
template<typename T>
struct st_max
{
    constexpr static T e = numeric_limits<T>::min();
    inline static T foo(T x, T y)
    {
        return max(x, y);
    }
    constexpr static T bar(T x)
    {
        return 1;
    }
};
template<typename T, typename t=st_sum<T>>
struct segment_tree
{
    struct node
    {
        T val, update, modify;
        bool modified;
        node *nl, *nr;
        node()
        {
            val = update = modified = 0;
            nl = nr = nullptr;
        }
        void inline pull()
        {
            val = t::foo(nl->val, nr->val);
        }
        void push(int l, int r)
        {
            int m = (l + r) >> 1;
            if (modified)
            {
                if (l != r)
                {
                    nl->modify = nr->modify = modify;
                    nl->modified = nr->modified = true;
                    nl->val = modify * t::bar(m - l + 1);
                    nr->val = modify * t::bar(r - m);
                    nl->update = nr->update = 0;
                }
                modified = modify = 0;
            }
            if (update)
            {
                if (l != r)
                {
                    nl->update += update;
                    nr->update += update;
                    nl->val += update * t::bar(m - l + 1);
                    nr->val += update * t::bar(r - m);
                }
                update = 0;
            }
        }
        T query(int ql, int qr, int l, int r)
        {
            if (ql > r || qr < l)
                return 0;
            if (ql <= l && r <= qr)
                return val;
            push(l, r);
            int m = (l + r) >> 1;
            return t::foo(nl->query(ql, qr, l, m), nr->query(ql, qr, m + 1, r));
        }
        void update(int ql, int qr, int d, int l, int r)
        {
            if (ql > r || qr < l)
                return;
            if (ql <= l && r <= qr)
            {
                update += d;
                val += d * t::bar(r - l + 1);
                return;
            }
            push(l, r);
            int m = (l + r) >> 1;
            nl->update(ql, qr, d, l, m);
            nr->update(ql, qr, d, m + 1, r);
            pull();
        }
        void modify(int ql, int qr, int k, int l, int r)
        {
            if (ql > r || qr < l)
                return;
            if (ql <= l && r <= qr)
            {
                if (update)
                    update = 0;
                modify = k;
                modified = true;
                val = k * t::bar(r - l + 1);
                return;
            }
            push(l, r);
            int m = (l + r) >> 1;
            nl->modify(ql, qr, k, l, m);
            nr->modify(ql, qr, k, m + 1, r);
            pull();
        }
    } * root;
    int n;
    vector<T> v;
    node *build(int l, int r)
    {
        node *n = new node();
        if (l == r)
        {
            n->val = v[l];
            return n;
        }
        int m = (l + r) >> 1;
        n->nl = build(l, m);
        n->nr = build(m + 1, r);
        n->pull();
        return n;
    }
    segment_tree(const vector<int> &_v) // assume 1-indexed array!
    {
        v = move(_v);
        n = v.size() - 1;
        root = build(1, n);
    }
    T inline query(int ql, int qr)
    {
        return root->query(ql, qr, 1, n);
    }
    void inline update(int ql, int qr, int d)
    {
        root->update(ql, qr, d, 1, n);
    }
    void inline modify(int ql, int qr, int k)
    {
        root->modify(ql, qr, k, 1, n);
    }
};