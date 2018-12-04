template<typename T, typename Merge>
class PST
{
	struct Node
	{
		int lidx, ridx;
		T value;
		int start, end;

		Node() = default;
		Node(int start_, int end_)
			:start(start_), end(end_), value(T()) {}
	};

public:
	PST(int n_, Merge m) : n(n_), merge(m)
	{
		root.push_back(init(0, n));
		raw.resize(n);
	}

	void modify(int idx, function<T(T)> modifier)
	{
		update(idx, modifier(raw[idx]));
	}

	void update(int idx, const T& value)
	{
		raw[idx] = value;
		int prev = root.back();
		root.emplace_back(_update(prev, idx, value, 0, n));
	}

	T query(int k, int start, int end)
	{
		return _query(root[k], start, end);
	}

private:

	int init(int start, int end)
	{
		int idx = node.size();
		node.emplace_back(start, end);

		if (start != end)
		{
			int mid = (start + end) / 2;

			node[idx].lidx = init(start, mid);
			node[idx].ridx = init(mid + 1, end);
		}

		return idx;
	}

	int _update(int prev, int idx, int value, int start, int end)
	{
		if (idx < start || idx > end)
			return prev;

		int nidx = node.size();
		node.emplace_back(start, end);

		if (start == end)
			node[nidx].value = value;
		else
		{
			int mid = (start + end) / 2;
			node[nidx].lidx = _update(node[prev].lidx, idx, value, start, mid);
			node[nidx].ridx = _update(node[prev].ridx, idx, value, mid + 1, end);
			node[nidx].value = merge(node[node[nidx].lidx].value, node[node[nidx].ridx].value);
		}

		return nidx;
	}

	int _query(int idx, int start, int end)
	{
		if (start <= node[idx].start && node[idx].end <= end)
			return node[idx].value;

		int mid = (node[idx].start + node[idx].end) / 2;

		if (mid < start)
			return _query(node[idx].ridx, start, end);

		if (mid + 1 > end)
			return _query(node[idx].lidx, start, end);

		return merge(_query(node[idx].lidx, start, end),
			_query(node[idx].ridx, start, end));
	}

	Merge merge;
	vector<T> raw;
	vector<int> root;
	vector<Node> node;
	int n;
};

template<typename T, typename Merge>
PST<T, Merge> pst(int n, Merge merge)
{
	return PST<T, Merge>(n, merge);
}