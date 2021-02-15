
random_device rd;
mt19937 mt(rd());
struct treap
{
    int key, pri, size;
    treap *tl, *tr;
    treap() = default;
    treap(int k) : key(k), pri(mt()), size(1)
    {
        tl = tr = nullptr;
    }
    ~treap()
    {
        if (tl)
            delete tl;
        if (tr)
            delete tr;
    }
    inline static int sz(treap *t)
    {
        return t ? t->size : 0;
    }
    void pull()
    {
        size = sz(tl) + 1 + sz(tr);
    }
};
inline int sz(treap *t)
{
    return t ? t->size : 0;
}
treap *merge(treap *a, treap *b)
{
    if (!a || !b)
        return a ?: b;
    if (a->pri < b->pri)
    {
        a->tr = merge(a->tr, b);
        a->pull();
        return a;
    }
    else
    {
        b->tl = merge(a, b->tl);
        b->pull();
        return b;
    }
}
void split(treap *t, int k, treap *&a, treap *&b)
{
    if (!t)
        a = b = nullptr;
    else if (t->key <= k)
    {
        a = t;
        split(t->tr, k, a->tr, b);
        a->pull();
    }
    else
    {
        b = t;
        split(t->tl, k, a, b->tl);
        b->pull();
    }
}