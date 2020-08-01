
template<int M = (int)1e9 + 7>
struct mint
{
    mint<M>() : value(0) { }
    mint<M>(int n) : value(n) { }
    mint<M>(i64 n) : value(n) { }

    mint<M> operator+(const mint<M>& r)
    {
        return (value + r.value) % M;
    }

    mint<M> operator-(const mint<M>& r)
    {
        return (value + M - r.value) % M;
    }

    mint<M> operator*(const mint<M>& r)
    {
        return (1ll * value * r.value) % M;
    }

    mint<M> operator/(const mint<M>& r)
    {
        return (1ll * value * r.inv()) % M;
    }

    int inv() const
    {
        return pow(M - 2).value;
    }

    mint<M> pow(i64 k) const
    {
        if (k == 0)
            return 1;

        auto half = pow(k / 2);
        half = half * half;

        if (k % 2 == 0)
            return half;
        else
            return half * value;
    }

    int value = 0;
};

template<int M>
istream& operator>>(istream& s, mint<M>& v)
{
    int k;
    s >> k;
    v.value = k % M;

    return s;
}

template<int M>
ostream& operator<<(ostream& s, const mint<M>& v)
{
    s << v.value;
    return s;
}