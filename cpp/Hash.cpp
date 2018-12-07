
class Hash
{
public:
	Hash(const string& s, i64 mod1 = 1e9 + 7, i64 mod2 = 1e9 + 9, i64 base_ = 256)
	{
		mod[0] = mod1;
		mod[1] = mod2;
		base = base_;

		for (int i = 0; i < 2; i++)
		{
			hash[i].resize(s.size());
			pw[i].resize(s.size());
			fill(s, i);
		}
	}

	i64 mod[2];
	i64 base = 256;

	ii64 get(int pos, int len)
	{
		return ii64(get(pos, len, 0), get(pos, len, 1));
	}

private:
	vector<i64> hash[2];
	vector<i64> pw[2];

	i64 get(int pos, int len, int idx)
	{
		i64 r = hash[idx][pos + len - 1];
		if (pos == 0)
			return r;

		i64 l = (hash[idx][pos - 1] * pw[idx][len]) % mod[idx];
		i64 h = (r - l + 100000 * mod[idx]) % mod[idx];

		return h;
	}

	void fill(const string& s, int idx)
	{
		hash[idx][0] = s[0];
		pw[idx][0] = 1;
		for (int i = 1; i < s.length(); i++)
			pw[idx][i] = (pw[idx][i - 1] * base) % mod[idx];

		for (int i = 1; i < s.length(); i++)
			hash[idx][i] = (hash[idx][i - 1] * base + s[i]) % mod[idx];
	}
};
