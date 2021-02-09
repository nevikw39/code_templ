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
        T val, tag_update, tag_modify;
        bool tag_modify_valid;
        node *nl, *nr;
        node()
        {
            val = tag_update = tag_modify_valid = 0;
            nl = nr = nullptr;
        }
        void inline pull()
        {
            val = t::foo(nl->val, nr->val);
        }
        void push(int l, int r)
        {
            int m = (l + r) >> 1;
            if (tag_modify_valid)
            {
                if (l != r)
                {
                    nl->tag_modify = nr->tag_modify = tag_modify;
                    nl->tag_modify_valid = nr->tag_modify_valid = true;
                    nl->val = tag_modify * t::bar(m - l + 1);
                    nr->val = tag_modify * t::bar(r - m);
                    nl->tag_update = nr->tag_update = 0;
                }
                tag_modify_valid = tag_modify = 0;
            }
            if (tag_update)
            {
                if (l != r)
                {
                    nl->tag_update += tag_update;
                    nr->tag_update += tag_update;
                    nl->val += tag_update * t::bar(m - l + 1);
                    nr->val += tag_update * t::bar(r - m);
                }
                tag_update = 0;
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
                tag_update += d;
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
                if (tag_update)
                    tag_update = 0;
                tag_modify = k;
                tag_modify_valid = true;
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