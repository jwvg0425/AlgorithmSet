class FenwickTree2D
{
public:
    FenwickTree2D(int n_, int m_)
        : n(n_), m(m_)
    {
        data.resize(n + 1, vector<i64>(m + 1));
    }

    i64 sum(int x, int y)
    {
        i64 ans = 0;

        for (int i = x; i > 0; i -= (i&-i))
            for (int j = y; j > 0; j -= (j&-j))
                ans += data[i][j];

        return ans;
    }

    void add(int x, int y, i64 num)
    {
        for (int i = x; i <= n; i += (i&-i))
            for (int j = y; j <= m; j += (j&-j))
                data[i][j] += num;
    }

private:
    int n, m;
    vector<vector<i64>> data;
};