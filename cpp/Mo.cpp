// use case : https://www.acmicpc.net/source/39925850
template<int BUCKET, typename Q, typename A, typename D>
class Mo
{
	struct QData
	{
		Q query;
		int lo, hi;
		int idx;
	};

public:
	template<typename Add, typename Erase>
	Mo(Add addFunc, Erase eraseFunc)
		: add(addFunc), erase(eraseFunc)
	{
	}

	void addQuery(Q data, int l, int r)
	{
		QData d;
		d.query = data;
		d.lo = l;
		d.hi = r;
		d.idx = qs.size();
		qs.push_back(d);
		ans.emplace_back();
	}

	vector<A> run(D state, A ansv)
	{
		sort(all(qs), [](const QData& l, const QData& r)
		{
			int lb = l.hi / BUCKET;
			int rb = r.hi / BUCKET;

			if (lb == rb)
				return l.lo < r.lo;

			return lb < rb;
		});

		int lo = 1, hi = 0;

		for (auto& q : qs)
		{
			int nlo = q.lo;
			int nhi = q.hi;

			while (lo > nlo)
			{
				lo--;
				add(lo, state, ansv);
			}

			while (hi < nhi)
			{
				hi++;
				add(hi, state, ansv);
			}

			while (lo < nlo)
			{
				erase(lo, state, ansv);
				lo++;
			}

			while (hi > nhi)
			{
				erase(hi, state, ansv);
				hi--;
			}

			ans[q.idx] = ansv;
		}

		return ans;
	}

private:
	using AddFunc = function<void(int, D&, A&)>;
	using EraseFunc = function<void(int, D&, A&)>;

	AddFunc add;
	EraseFunc erase;

	vector<QData> qs;
	vector<A> ans;
};
