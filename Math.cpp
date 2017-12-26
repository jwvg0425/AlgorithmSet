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
        return sieve[k] == 0;
    }

private:
    void init()
    {
        for (int i = 2; i <= N; i++)
        {
            if (sieve[i] != 0)
                continue;

            primes.push_back(i);

            for (int j = i; j <= N; j++)
            {
                sieve[j] = i;
            }
        }
    }

    vector<int> primes;
    int sieve[N + 1];
};

class Mapping
{
public:
    void init(const vector<int>& raw)
    {
        arr = raw;
        sort(arr.begin(), arr.end());

        for (int i = 0; i < arr.size(); i++)
            idx[arr[i]] = i;
    }

    int get_idx(int k)
    {
        return idx[k];
    }

    int get_value(int idx)
    {
        return arr[idx];
    }

private:
    vector<int> arr;
    map<int, int> idx;
};