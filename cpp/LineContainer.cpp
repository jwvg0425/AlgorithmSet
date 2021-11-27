// kx + m
struct Line
{
    mutable i64 k, m, p;
    bool operator<(const Line& other) const
    {
        return  k < other.k;
    }

    bool operator<(i64 x) const
    {
        return p < x;
    }
};

struct LineContainer : multiset<Line, less<>>
{
    const i64 inf = 1ll << 61;

    i64 div(i64 a, i64 b)
    {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y)
    {
        if (y == end())
        {
            x->p = inf;
            return false;
        }

        if (x->k == y->k)
            x->p = (x->m > y->m) ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);

        return x->p >= y->p;
    }

    void add(i64 k, i64 m)
    {
        auto z = insert({ k, m, 0 });
        auto y = z++;
        auto x = y;

        while (isect(y, z))
            z = erase(z);

        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));

        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }

    i64 query(i64 x)
    {
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
