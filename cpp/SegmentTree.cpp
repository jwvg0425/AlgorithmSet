constexpr int clog2(int n) { return ((n < 2) ? 1 : 1 + clog2(n / 2)); }

template<typename T>
class SegmentTree
{
public:
    template<typename M>
    SegmentTree(const M& m): merge(m) {}

    void init(vector<T>& raw_)
    {
        raw = raw_;
        n = (int)raw.size();
        int sz = (1 << (clog2(n) + 1));
        data.resize(sz);

        _init(raw, 1, 0, n - 1);
    }

    T modify(int idx, function<T(T)> modifier) { return update(idx, modifier(raw[idx])); }
    T update(int idx, const T& newVal) { raw[idx] = newVal; return _update(1, 0, n - 1, idx, newVal); }
    T query(int left, int right) { return _query(1, 0, n - 1, left, right); }

private:
    vector<T> raw;
    vector<T> data;
    int n;
    using Merge = function<T(const T&, const T&)>;
    Merge merge;

    T _init(vector<T>& raw, int node, int start, int end)
    {
        int mid = (start + end) / 2;
        if (start == end)
            return data[node] = raw[start];
        else
            return data[node] = merge(_init(raw, node * 2, start, mid),
                _init(raw, node * 2 + 1, mid + 1, end));
    }

    T _update(int node, int start, int end, int index, const T& newVal)
    {
        if (index < start || index > end)
            return data[node];

        if (start == end)
            data[node] = newVal;
        else
        {
            int mid = (start + end) / 2;
            data[node] = merge(_update(node * 2, start, mid, index, newVal),
                _update(node * 2 + 1, mid + 1, end, index, newVal));
        }

        return data[node];
    }

    T _query(int node, int start, int end, int left, int right)
    {
        if (left <= start && end <= right)
            return data[node];

        int mid = (start + end) / 2;

        if (mid < left)
            return _query(node * 2 + 1, mid + 1, end, left, right);

        if (mid + 1 > right)
            return _query(node * 2, start, mid, left, right);

        return merge(_query(node * 2, start, mid, left, right),
            _query(node * 2 + 1, mid + 1, end, left, right));
    }
};
