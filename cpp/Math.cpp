template<int N>
class Sieve
{
public:
    Sieve<N>()
    {
        init();
    }

    const vector<int>& getPrimes() const
    {
        return primes;
    }

    bool isPrime(int k)
    {
        assert(0 <= k && k <= N);
        return sieve[k] != 0;
    }

private:
    void init()
    {
        for (int i = 2; i <= N; i++)
        {
            if (sieve[i] != 0)
                continue;

            primes.push_back(i);

            for (int j = i; j <= N; j+=i)
            {
                sieve[j] = i;
            }
        }
    }

    vector<int> primes;
    int sieve[N + 1];
};

template<typename T>
class Mapping
{
public:
	void init(const vector<T>& raw, int base = 0)
	{
		start = base;
		arr = raw;
		sort(arr.begin(), arr.end());
		arr.erase(unique(arr.begin(), arr.end()), arr.end());
	}

	int get_idx(T k)
	{
		return start + (lower_bound(all(arr), k) - arr.begin());
	}

	T get_value(int idx)
	{
		return arr[idx - start];
	}

	int size()
	{
		return arr.size();
	}

private:
	int start = 0;
	vector<T> arr;
};

template<int N>
class Factorization
{
public:
    Factorization()
    {
        init();
    }

    void init()
    {
        for (int i = 2; i <= N; i++)
        {
            if (minP[i] != 0)
                continue;

            for (int j = i; j <= N; j += i)
                if (minP[j] == 0)
                    minP[j] = i;
        }
    }

    // O(logN)
    vector<int> seq(int n)
    {
        vector<int> res;
        while (n > 1)
        {
            res.push_back(minP[n]);
            n /= minP[n];
        }

        return res;
    }

    // O(logN) (prime, count)
    vector<ii> group(int n)
    {
        vector<ii> res;

        while (n > 1)
        {
            int cnt = 0;
            int p = minP[n];
            while (n % p == 0)
            {
                n /= p;
                cnt++;
            }

            res.emplace_back(p, cnt);
        }

        return res;
    }

private:
    int minP[N + 5];
};

ii64 gcd_ext(i64 a, i64 b)
{
    if (a == 0)
        return ii64(0, 1);
    if (b == 0)
        return ii64(1, 0);

    auto [xp, yp] = gcd_ext(b, a % b);

    auto x = yp;
    auto y = xp - a / b * x;
    return ii64(x, y);
}
