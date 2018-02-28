constexpr int clog2(int n)
{
    return ((n < 2) ? 1 : 1 + clog2(n / 2));
}

template<int Size>
class MergeSortTree
{
public:
    void init(vector<int>& raw)
    {
        build(1, 0, raw.size() - 1, raw);
        n = raw.size();
    }

    //l,r 구간에서 k보다 작은 수의 개수
    int query(int l, int r, int k)
    {
        return query_internal(1, 0, n - 1, l, r, k);
    }

private:
    int query_internal(int node, int l, int r, int x, int y, int k)
    {
        if (r < x || l > y)
            return 0;

        if (x <= l && r <= y)
        {
            return upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin();
        }

        int mid = (l + r) / 2;
        return query_internal(2 * node, l, mid, x, y, k) +
            query_internal(2 * node + 1, mid + 1, r, x, y, k);
    }

    void build(int node, int l, int r, vector<int>& raw)
    {
        if (l == r)
        {
            tree[node].push_back(raw[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid, raw);
        build(node * 2 + 1, mid + 1, r, raw);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> merge(const vector<int>& l, const vector<int>& r)
    {
        vector<int> res;
        int lidx = 0, ridx = 0;

        while (lidx < l.size() && ridx < r.size())
        {
            if (l[lidx] < r[ridx])
                res.push_back(l[lidx++]);
            else
                res.push_back(r[ridx++]);
        }

        while (lidx < l.size())
            res.push_back(l[lidx++]);

        while (ridx < r.size())
            res.push_back(r[ridx++]);

        return res;
    }

    vector<int> tree[2 << clog2(Size)];
    int n;
};