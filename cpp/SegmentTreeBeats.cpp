
// use case : https://www.acmicpc.net/source/51773400

constexpr int clog2(int n) { return ((n < 2) ? 1 : 1 + clog2(n / 2)); }

template<typename T, typename L>
class SegTreeBeats
{
public:
    SegTreeBeats(L dl = L()) : dlazy(dl)
    {
    }

    void init(vector<T> arr)
    {
        n = (int)arr.size();
        int sz = (1 << (clog2(n) + 1));
        tree.resize(sz);
        lazy.resize(sz, dlazy);

        _init(arr, 0, n - 1, 1);
    }

    void update_range(int left, int right, L diff) { _update_range(0, n - 1, 1, left, right, diff); }

    T query(int left, int right) { return _query(1, 0, n - 1, left, right); }

private:
    T _init(vector<T>& arr, int start, int end, int node)
    {
        if (start == end)
            return tree[node] = arr[start];

        int mid = (start + end) / 2;

        return tree[node] = node_merge(_init(arr, start, mid, node * 2), _init(arr, mid + 1, end, node * 2 + 1));
    }

    void update_lazy(int start, int end, int node)
    {
        if (lazy[node] == dlazy)
            return;

        tree[node] = apply_lazy(start, end, tree[node], lazy[node]);

        if (start != end)
        {
            lazy[node * 2] = lazy_merge(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = lazy_merge(lazy[node * 2 + 1], lazy[node]);
        }

        lazy[node] = dlazy;
    }

    void _update_range(int start, int end, int node, int left, int right, L diff)
    {
        update_lazy(start, end, node);

        if (break_condition(tree[node], diff, start, end, left, right))
            return;

        if (tag_condition(tree[node], diff, start, end, left, right))
        {
            lazy[node] = lazy_merge(lazy[node], diff);
            update_lazy(start, end, node);
            return;
        }

        int mid = (start + end) / 2;
        _update_range(start, mid, node * 2, left, right, diff);
        _update_range(mid + 1, end, node * 2 + 1, left, right, diff);
        tree[node] = node_merge(tree[node * 2], tree[node * 2 + 1]);
    }

    T _query(int node, int start, int end, int left, int right)
    {
        update_lazy(start, end, node);

        if (left <= start && end <= right)
            return tree[node];

        int mid = (start + end) / 2;

        if (mid < left)
            return _query(node * 2 + 1, mid + 1, end, left, right);

        if (mid + 1 > right)
            return _query(node * 2, start, mid, left, right);

        return node_merge(_query(node * 2, start, mid, left, right),
            _query(node * 2 + 1, mid + 1, end, left, right));
    }

    L dlazy;

    int n = 0;
    vector<T> tree;
    vector<L> lazy;
};
