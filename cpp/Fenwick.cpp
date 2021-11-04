

class FenwickTree
{
public:
    FenwickTree(int k)
    {
        data.resize(k);
        while ((1ll << (bit + 1)) < k)
            bit++;
    }

    i64 sum(int n)
    {
        i64 ans = 0;

        while (n > 0)
        {
            ans += data[n];
            n -= (n & -n);
        }

        return ans;
    }

    void add(int n, i64 num)
    {
        while (n < data.size())
        {
            data[n] += num;
            n += (n & -n);
        }
    }

    int kth(i64 k)
    {
        int ret = 0;
        for (int i = bit; i >= 0; i--)
        {
            i64 t = ret + (1 << i);
            if (t < data.size() && data[t] < k)
                k -= data[ret = t];
        }

        return ret + 1;
    }

private:
    vector<i64> data;
    int bit;
};