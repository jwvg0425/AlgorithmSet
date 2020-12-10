
using ui64 = unsigned long long int;

vector<ui64> alist = { 2, 3, 5, 7, 11 };

ui64 ipow(ui64 x, ui64 y, ui64 m)
{
	if (y == 0)
		return 1ll % m;

	ui64 half = ipow(x, y / 2, m);
	half = (half * half) % m;
	if (y % 2 == 0)
		return half;

	return (half * x) % m;
}

bool miller_rabin(ui64 n, ui64 a)
{
	ui64 d = n - 1;
	while (d % 2 == 0)
	{
		if (ipow(a, d, n) == n - 1)
			return true;

		d /= 2;
	}

	ui64 check = ipow(a, d, n);
	return check == n - 1 || check == 1;
}

// condition: n < 2^32
bool is_prime(ui64 n)
{
	if (n <= 1)
		return false;

	for (auto& a : alist)
		if (!miller_rabin(n, a))
			return false;

	return true;
}
