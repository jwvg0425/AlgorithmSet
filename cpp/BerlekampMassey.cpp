
template<int MOD>
class BerlekampMassey
{
public:
	i64 ipow(i64 x, i64 p)
	{
		i64 ret = 1, piv = x;
		while (p)
		{
			if (p & 1)
				ret = ret * piv % MOD;

			piv = piv * piv % MOD;
			p >>= 1;
		}
		return ret;
	}

	vector<int> findLinearRecurrence(vector<int> x)
	{
		vector<int> ls, cur;
		int lf, ld;
		for (int i = 0; i < x.size(); i++)
		{
			i64 t = 0;
			for (int j = 0; j < cur.size(); j++)
				t = (t + 1ll * x[i - j - 1] * cur[j]) % MOD;

			if ((t - x[i]) % MOD == 0)
				continue;

			if (cur.empty())
			{
				cur.resize(i + 1);
				lf = i;
				ld = (t - x[i]) % MOD;
				continue;
			}

			i64 k = -(x[i] - t) * ipow(ld, MOD - 2) % MOD;
			vector<int> c(i - lf - 1);
			c.push_back(k);

			for (auto& j : ls)
				c.push_back(-j * k % MOD);

			if (c.size() < cur.size())
				c.resize(cur.size());

			for (int j = 0; j < cur.size(); j++)
				c[j] = (c[j] + cur[j]) % MOD;

			if (i - lf + (int)ls.size() >= (int)cur.size())
				tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % MOD);

			cur = c;
		}

		for (auto& i : cur)
			i = (i % MOD + MOD) % MOD;

		return cur;
	}

	int getNth(vector<int> rec, vector<int> dp, i64 n)
	{

		int m = rec.size();
		vector<int> s(m), t(m);
		s[0] = 1;
		if (m != 1)
			t[1] = 1;
		else
			t[0] = rec[0];

		auto mul = [&rec](vector<int> v, vector<int> w)
		{
			int m = v.size();
			vector<int> t(2 * m);
			for (int j = 0; j < m; j++)
			{
				for (int k = 0; k < m; k++)
				{
					t[j + k] += 1ll * v[j] * w[k] % MOD;
					if (t[j + k] >= MOD)
						t[j + k] -= MOD;
				}
			}
			for (int j = 2 * m - 1; j >= m; j--)
			{
				for (int k = 1; k <= m; k++)
				{
					t[j - k] += 1ll * t[j] * rec[k - 1] % MOD;
					if (t[j - k] >= MOD)
						t[j - k] -= MOD;
				}
			}

			t.resize(m);
			return t;
		};

		while (n)
		{
			if (n & 1)
				s = mul(s, t);

			t = mul(t, t);
			n >>= 1;
		}

		i64 ret = 0;
		for (int i = 0; i < m; i++)
			ret += 1ll * s[i] * dp[i] % MOD;

		return ret % MOD;
	}

	int guessNthTerm(vector<int> x, i64 n)
	{
		if (n < x.size())
			return x[n];

		vector<int> v = findLinearRecurrence(x);
		if (v.empty())
			return 0;

		return getNth(v, x, n);
	}

	struct elem { int x, y, v; }; // A_(x, y) <- v, 0-based. no duplicate please..
	vector<int> getMinPoly(int n, vector<elem> M)
	{
		// smallest poly P such that A^i = sum_{j < i} {A^j \times P_j}
		vector<int> rnd1, rnd2;
		mt19937 rng(0x14004);
		auto randint = [&rng](int lb, int ub)
		{
			return uniform_int_distribution<int>(lb, ub)(rng);
		};

		for (int i = 0; i < n; i++)
		{
			rnd1.push_back(randint(1, MOD - 1));
			rnd2.push_back(randint(1, MOD - 1));
		}

		vector<int> gobs;
		for (int i = 0; i < 2 * n + 2; i++)
		{
			int tmp = 0;
			for (int j = 0; j < n; j++)
			{
				tmp += 1ll * rnd2[j] * rnd1[j] % MOD;
				if (tmp >= MOD)
					tmp -= MOD;
			}
			gobs.push_back(tmp);
			vector<int> nxt(n);
			for (auto& i : M)
			{
				nxt[i.x] += 1ll * i.v * rnd1[i.y] % MOD;
				if (nxt[i.x] >= MOD)
					nxt[i.x] -= MOD;
			}
			rnd1 = nxt;
		}
		auto sol = findLinearRecurrence(gobs);
		reverse(sol.begin(), sol.end());
		return sol;
	}
	i64 det(int n, vector<elem> M)
	{
		vector<int> rnd;
		mt19937 rng(0x14004);
		auto randint = [&rng](int lb, int ub)
		{
			return uniform_int_distribution<int>(lb, ub)(rng);
		};

		for (int i = 0; i < n; i++)
			rnd.push_back(randint(1, MOD - 1));

		for (auto& i : M)
			i.v = 1ll * i.v * rnd[i.y] % MOD;

		auto sol = get_min_poly(n, M)[0];

		if (n % 2 == 0)
			sol = MOD - sol;

		for (auto& i : rnd)
			sol = 1ll * sol * ipow(i, MOD - 2) % MOD;

		return sol;
	}
};
