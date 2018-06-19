class FenwickTree
{
public:
    FenwickTree(int k)
    {
        data.resize(k);
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

    int search(i64 k)
    {
        int lo = 0, hi = data.size() - 1;
        int ans = 0;

        while (lo <= hi)
        {
            int mid = (lo + hi) / 2;

            i64 q = sum(mid);

            if (q >= k)
            {
                ans = mid;
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
        }

        return ans;
    }

private:
    vector<i64> data;
};