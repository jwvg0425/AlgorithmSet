
template<typename T>
vector<T> getXORBasis(vector<T> arr)
{
	vector<T> basis;
	while (true)
	{
		i64 m = *max_element(all(arr));
		if (m == 0)
			break;

		basis.push_back(m);
		for (auto& ai : arr)
			ai = min(ai, ai ^ m);
	}

	return basis;
}
