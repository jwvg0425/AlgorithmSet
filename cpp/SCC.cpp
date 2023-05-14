
template<int SZ>
struct Scc
{
	vector<int> edges[SZ];
	bool visited[SZ] = { false, }; // scc�� �̹� ���Ե� ��� true
	int discover[SZ] = { 0, };
	int cidx[SZ] = { 0, };
	// scc�� ����
	vector<int> sedges[SZ];
	stack<int> s;
	vector<vector<int>> scc;
	int idx = 1;

	int dfs(int k)
	{
		s.push(k);

		discover[k] = idx++;

		int ret = discover[k];

		for (auto& edge : edges[k])
		{
			if (visited[edge])
				continue;

			if (discover[edge] != 0)
			{
				ret = min(discover[edge], ret);
				continue;
			}

			ret = min(dfs(edge), ret);
		}

		if (discover[k] == ret)
		{
			vector<int> newScc;

			while (true)
			{
				int t = s.top();
				s.pop();

				visited[t] = true;
				newScc.push_back(t);

				if (t == k)
					break;
			}

			sort(newScc.begin(), newScc.end());

			scc.push_back(newScc);
		}

		return ret;
	}

	void calc_scc(int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (!visited[i])
				dfs(i);
		}

		sort(all(scc), [](const vector<int>& l, const vector<int>& r)
			{
				return l[0] < r[0];
			});

		for (int i = 0; i < scc.size(); i++)
		{
			for (auto& v : scc[i])
				cidx[v] = i;
		}

		for (int i = 0; i < scc.size(); i++)
		{
			for (auto& v : scc[i])
			{
				for (auto& e : edges[v])
				{
					if (cidx[e] == i)
						continue;
					sedges[i].push_back(cidx[e]);
				}
			}

			sort(all(sedges[i]));
			sedges[i].erase(unique(all(sedges[i])), sedges[i].end());
		}
	}
};