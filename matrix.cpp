template <typename T = int64_t, T N = 2, T M = 1e9 + 7>
struct matrix
{
    using vec = array<T, N>;
    array<vec, N> a{};
    matrix() = default;
    matrix(const matrix &x) = default;
    matrix(const initializer_list<T> &il)
    {
        assert(il.size() == N * N);
        auto itr = il.begin();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                a[i][j] = *itr++;
    }
    matrix(const initializer_list<initializer_list<T>> &il)
    {
        assert(il.size() == N);
        auto itr = il.begin();
        for (int i = 0; i < N; i++)
        {
            const auto &jl = *itr++;
            assert(jl.size() == N);
            auto jtr = jl.begin();
            for (int j = 0; j < N; j++)
                a[i][j] = *jtr++;
        }
    }
    matrix(const array<vec, N> &_a) : a(_a) {}
    bool operator==(const matrix &x) const
    {
        return a == x.a;
    }
    matrix operator*(const matrix &x) const
    {
        matrix y;
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    y.a[i][j] = (y.a[i][j] + a[i][k] * x.a[k][j] % M) % M;
        return move(y);
    }
    vec operator*(const vec &x) const
    {
        vec y{};
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                y[i] = (y[i] + a[i][j] * x[j] % M) % M;
        return move(y);
    }
    matrix power(int n) const
    {
        matrix y, x = *this;
        for (int i = 0; i < N; i++)
            y.a[i][i] = 1;
        while (n)
        {
            if (n & 1)
                y = y * x;
            x = x * x;
            n >>= 1;
        }
        return move(y);
    }
};