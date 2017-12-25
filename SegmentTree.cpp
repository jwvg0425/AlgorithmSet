template<typename T>
class SegmentTree
{
public:
    using MergeFunc = function<T(const T&, const T&)>;

    SegmentTree(vector<T>& raw, const MergeFunc& func)
        : merge(func), n(raw.size())
    {
        int h = (int)ceil(log2(n));
        int tree_size = (1 << (h + 1));
        data.resize(tree_size);

        init(raw, 1, 0, n - 1);
    }

    T update(int idx, const T& newVal)
    {
        return update_internal(1, 0, n - 1, idx, newVal);
    }

    T query(int left, int right)
    {
        return query_internal(1, 0, n - 1, left, right);
    }

private:
    vector<T> data;
    MergeFunc merge;
    int n;

    T init(vector<T>& raw, int node, int start, int end)
    {
        int mid = (start + end) / 2;
        if (start == end)
            return data[node] = raw[start];
        else
            return data[node] = merge(init(raw, node * 2, start, mid),
                init(raw, node * 2 + 1, mid + 1, end));
    }

    T update_internal(int node, int start, int end, int index, const T& newVal)
    {
        if (index < start || index > end)
            return data[node];

        if (start == end)
        {
            data[node] = newVal;
        }
        else
        {
            int mid = (start + end) / 2;
            data[node] = merge(update_internal(node * 2, start, mid, index, newVal),
                update_internal(node * 2 + 1, mid + 1, end, index, newVal));
        }

        return data[node];
    }

    T query_internal(int node, int start, int end, int left, int right)
    {
        if (left <= start && end <= right)
            return data[node];

        int mid = (start + end) / 2;

        if (mid < left)
            return query_internal(node * 2 + 1, mid + 1, end, left, right);

        if (mid + 1 > right)
            return query_internal(node * 2, start, mid, left, right);

        return merge(query_internal(node * 2, start, mid, left, right),
            query_internal(node * 2 + 1, mid + 1, end, left, right));
    }
};