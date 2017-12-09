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

private:
	vector<i64> data;
};