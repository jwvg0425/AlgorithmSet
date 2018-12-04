class PST
{
    struct Node
    {
        int lidx, ridx;
        int value;
        int start, end;

        Node() = default;
        Node(int start_, int end_)
            :start(start_), end(end_), value(0) {}
    };
public:
    PST(int n_) : n(n_)
    {
        root.push_back(init(0, n));
    }

    int init(int start, int end)
    {
        int idx = node.size();
        node.emplace_back(start, end);
        if (start + 1 < end)
        {
            int mid = (start + end) / 2;
            node[idx].lidx = init(start, mid);
            node[idx].ridx = init(mid, end);
        }
        return idx;
    }

    void update(int idx, int value)
    {
        int prev = root.back();
        root.emplace_back(update(prev, idx, value, 0, n));
    }

    int sum(int k, int start, int end)
    {
        return sum_internal(root[k], start, end);
    }

private:
    int update(int prev, int idx, int value, int start, int end)
    {
        if (end <= idx || idx < start)
            return prev;

        int nidx = node.size();
        node.emplace_back(start, end);

        if (start + 1 == end)
        {
            node[nidx].value = node[prev].value + value;
        }
        else
        {
            int mid = (start + end) / 2;
            node[nidx].lidx = update(node[prev].lidx, idx, value, start, mid);
            node[nidx].ridx = update(node[prev].ridx, idx, value, mid, end);
            node[nidx].value = node[node[nidx].lidx].value + node[node[nidx].ridx].value;
        }

        return nidx;
    }

    int sum_internal(int idx, int start, int end)
    {
        if (end <= node[idx].start || node[idx].end <= start)
            return 0;

        if (start <= node[idx].start && node[idx].end <= end)
            return node[idx].value;

        return sum_internal(node[idx].lidx, start, end) +
            sum_internal(node[idx].ridx, start, end);
    }

    vector<int> root;
    vector<Node> node;
    int n;
};