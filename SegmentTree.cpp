template<typename T>
class SegmentTree
{
public:
    void init(vector<T>& raw)
    {
        assert(!is_init);
        is_init = true;
        n = raw.size();
        int h = (int)ceil(log2(n));
        int tree_size = (1 << (h + 1));
        data.resize(tree_size);

        init_internal(raw, 1, 0, n - 1);
    }

    T update(int idx, const T& newVal)
    {
        assert(is_init);
        return update_internal(1, 0, n - 1, idx, newVal);
    }

    T query(int left, int right)
    {
        assert(is_init);
        return query_internal(1, 0, n - 1, left, right);
    }

    virtual T merge(const T& left, const T& right) = 0;
    virtual T merge_with_idx(const T& left, const T& right, int left_idx, int right_idx)
    {
        return merge(left, right);
    }

private:
    vector<T> data;
    int n;
    bool is_init = false;

    T init_internal(vector<T>& raw, int node, int start, int end)
    {
        int mid = (start + end) / 2;
        if (start == end)
            return data[node] = raw[start];
        else
            return data[node] = merge_with_idx(init_internal(raw, node * 2, start, mid),
                init_internal(raw, node * 2 + 1, mid + 1, end), node * 2, node * 2 + 1);
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
            data[node] = merge_with_idx(update_internal(node * 2, start, mid, index, newVal),
                update_internal(node * 2 + 1, mid + 1, end, index, newVal), node * 2, node * 2 + 1);
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

        return merge_with_idx(query_internal(node * 2, start, mid, left, right),
            query_internal(node * 2 + 1, mid + 1, end, left, right), node * 2, node * 2 + 1);
    }
};
