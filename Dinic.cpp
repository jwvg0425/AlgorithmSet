template<int Size>
class Dinic
{
public:
	//a,b간에 capacity c인 엣지 추가
	void addEdge(int a, int b, int c)
	{
		capa[a][b] = c;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int maxFlow(int source, int sink)
	{
		int totalFlow = 0;

		while (bfs(source, sink))
		{
			memset(work, 0, sizeof(work));

			while (true)
			{
				int flow = dfs(source, sink, 987654321);

				if (flow == 0)
					break;

				totalFlow += flow;
			}
		}

		return totalFlow;
	}

private:
	std::vector<int> adj[Size];
	int flow[Size][Size];
	int capa[Size][Size];
	int level[Size];
	int work[Size];

	bool bfs(int source, int sink)
	{
		memset(level, -1, sizeof(level));

		level[source] = 0;

		std::queue<int> q;
		q.push(source);

		while (!q.empty())
		{
			int now = q.front();
			q.pop();

			for (auto& e : adj[now])
			{
				if (level[e] != -1 || capa[now][e] - flow[now][e] <= 0)
					continue;

				level[e] = level[now] + 1;
				q.push(e);
			}
		}

		return level[sink] != -1;
	}

	int dfs(int s, int e, int f)
	{
		if (s == e)
			return f;

		for (int& i = work[s]; i < adj[s].size(); i++)
		{
			int next = adj[s][i];

			if (level[next] != level[s] + 1 || capa[s][next] - flow[s][next] <= 0)
				continue;

			int df = dfs(next, e, std::min(f, capa[s][next] - flow[s][next]));

			if (df != 0)
			{
				flow[s][next] += df;
				flow[next][s] -= df;
				return df;
			}
		}

		return 0;
	}
};