vector<int> edges[10001];
bool visited[10001]; // scc에 이미 포함된 경우 true
int discover[10001];
int cidx[10005];
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
	for (int i = 1; i <= n; i++)
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
}