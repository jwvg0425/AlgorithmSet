// use case : https://www.acmicpc.net/source/39925000

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
	template<typename Add, typename Erase, typename AFunc>
	Mo(Add addFunc, Erase eraseFunc, AFunc getAnsFunc)
		: add(addFunc), erase(eraseFunc), getAns(getAnsFunc)
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

	vector<A> run(D state)
	{
		sort(all(qs), [](const QData& l, const QData& r)
		{
			int lb = l.hi / BUCKET;
			int rb = r.hi / BUCKET;

			if (lb == rb)
				return l.lo < r.lo;

			return lb < rb;
		});

		int lo = 1, hi = 1;

		for (auto& q : qs)
		{
			int nlo = q.lo;
			int nhi = q.hi;

			while (lo > nlo)
			{
				lo--;
				add(lo, state);
			}

			while (hi < nhi)
			{
				hi++;
				add(hi, state);
			}

			while (lo < nlo)
			{
				erase(lo, state);
				lo++;
			}

			while (hi > nhi)
			{
				erase(hi, state);
				hi--;
			}

			ans[q.idx] = getAns(state);
		}

		return ans;
	}

private:
	using AddFunc = function<void(int, D&)>;
	using EraseFunc = function<void(int, D&)>;
	using AnsFunc = function<A(const D&)>;

	AddFunc add;
	EraseFunc erase;
	AnsFunc getAns;

	vector<QData> qs;
	vector<A> ans;
};
