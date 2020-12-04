
template<typename T>
class PST
{
	struct Node
	{
		int lidx, ridx;
		T value;

		Node() :value(T()), lidx(0), ridx(0) {}
	};

public:
	template<typename M>
	PST(int n_, const M& m) : n(n_), merge(m) {}


	int update(int idx, const T& value)
	{
		return update((int)root.size() - 1, idx, value);
	}

	int update(int pre, int idx, const T& value)
	{
		root.emplace_back(_update(root[pre], idx, value, 0, n));
		return (int)root.size() - 1;
	}

	T query(int k, int start, int end)
	{
		return _query(root[k], start, end, 0, n);
	}

	void init()
	{
		root.push_back(init(0, n));
	}

private:
	int init(int start, int end)
	{
		int idx = node.size();
		node.emplace_back();

		if (start != end)
		{
			int mid = (start + end) / 2;

			node[idx].lidx = init(start, mid);
			node[idx].ridx = init(mid + 1, end);
		}
		return idx;
	}

	int _update(int prev, int idx, const T& value, int start, int end)
	{
		if (idx < start || idx > end)
			return prev;

		int nidx = node.size();
		node.emplace_back();

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

	T _query(int idx, int start, int end, int left, int right)
	{
		if (start <= left && right <= end)
			return node[idx].value;

		int mid = (left + right) / 2;

		if (mid + 1 > end)
			return _query(node[idx].lidx, start, end, left, mid);

		if (mid < start)
			return _query(node[idx].ridx, start, end, mid + 1, right);

		return merge(_query(node[idx].lidx, start, end, left, mid),
			_query(node[idx].ridx, start, end, mid + 1, right));
	}

	using Merge = function<T(const T&, const T&)>;
	Merge merge;
	vector<int> root;
	vector<Node> node;
	int n;
};