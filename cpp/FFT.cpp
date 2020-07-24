using base = complex<double>;

void fft(vector<base>& a, bool inv)
{
    int n = a.size(), j = 0;
    vector<base> roots(n / 2);

    for (int i = 1; i < n; i++)
    {
        int bit = (n >> 1);
        while (j >= bit)
        {
            j -= bit;
            bit >>= 1;
        }

        j += bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
    for (int i = 0; i < n / 2; i++)
        roots[i] = base(cos(ang * i), sin(ang * i));

    for (int i = 2; i <= n; i <<= 1)
    {
        int step = n / i;
        for (int j = 0; j < n; j += i)
        {
            for (int k = 0; k < i / 2; k++)
            {
                base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
        }
    }

    if (!inv)
        return;

    for (int i = 0; i < n; i++)
        a[i] /= n;
}

vector<i64> multiply(vector<i64>& v, vector<i64>& w)
{
    vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2;

    while (n < v.size() + w.size())
        n <<= 1;

    fv.resize(n);
    fw.resize(n);

    fft(fv, false);
    fft(fw, false);

    for (int i = 0; i < n; i++)
        fv[i] *= fw[i];

    fft(fv, true);

    vector<i64> ret(n);

    for (int i = 0; i < n; i++)
        ret[i] = (i64)round(fv[i].real());

    return ret;
}