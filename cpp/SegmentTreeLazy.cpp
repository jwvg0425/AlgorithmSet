constexpr int clog2(int n) { return ((n < 2) ? 1 : 1 + clog2(n / 2)); }

class SegTreeLazy
{
public:
	i64 init(vector<i64> arr)
	{
		n = (int)arr.size();
		int sz = (1 << (clog2(n) + 1));
		tree.resize(sz);
		lazy.resize(sz);

		_init(arr, 0, n - 1, 1);
	}

	void update_range(int left, int right, i64 diff) { _update_range(0, n - 1, 1, left, right, diff); }

	i64 query(int left, int right) { return _query(0, n - 1, 1, left, right); }

private:
	i64 _init(vector<i64>& arr, int start, int end, int node)
	{
		if (start == end)
			return tree[node] = arr[start];

		int mid = (start + end) / 2;

		return tree[node] = _init(arr, start, mid, node * 2) + _init(arr, mid + 1, end, node * 2 + 1);
	}

	void update_lazy(int start, int end, int node)
	{
		if (lazy[node] == 0)
			return;

		tree[node] += (end - start + 1) * lazy[node];

		if (start != end)
		{
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}

		lazy[node] = 0;
	}

	void _update_range(int start, int end, int node, int left, int right, i64 diff)
	{
		update_lazy(start, end, node);

		if (left > end || right < start)
			return;

		if (left <= start && end <= right)
		{
			tree[node] += (end - start + 1) * diff;

			if (start != end)
			{
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}

			return;
		}

		int mid = (start + end) / 2;
		_update_range(start, mid, node * 2, left, right, diff);
		_update_range(mid + 1, end, node * 2 + 1, left, right, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	i64 _query(int start, int end, int node, int left, int right)
	{
		update_lazy(start, end, node);

		if (left > end || right < start)
			return 0;

		if (left <= start && end <= right)
		{
			return tree[node];
		}

		int mid = (start + end) / 2;
		return _query(start, mid, node * 2, left, right) +
			_query(mid + 1, end, node * 2 + 1, left, right);
	}

	int n = 0;
	vector<i64> tree;
	vector<i64> lazy;
};
