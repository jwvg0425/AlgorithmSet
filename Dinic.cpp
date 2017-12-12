struct Edge
{
	int end;
	i64 capa, flow;
	Edge* dual;

	Edge() : Edge(-1, 0) {}
	Edge(int e, i64 c) : end(e), capa(c), flow(0), dual(nullptr) {}

	i64 remain()
	{
		return capa - flow;
	}

	void addFlow(i64 f)
	{
		flow += f;
		dual->flow -= f;
	}
};

template<int Size>
class Dinic
{
public:

	const i64 INFINITE = 1ll << 62;
	~Dinic()
	{
		for (auto& a : adj)
		{
			for (auto& e : a)
			{
				delete e;
			}
		}
	}

	Edge* addEdge(int a, int b, i64 c)
	{
		auto e1 = new Edge(b, c);
		auto e2 = new Edge(a, 0);
		e1->dual = e2;
		e2->dual = e1;

		adj[a].push_back(e1);
		adj[b].push_back(e2);

		return e1;
	}

	i64 maxFlow(int source, int sink)
	{
		i64 totalFlow = 0;

		while (bfs(source, sink))
		{
			memset(work, 0, sizeof(work));

			while (true)
			{
				i64 flow = dfs(source, sink, INFINITE);

				if (flow == 0)
					break;

				totalFlow += flow;
			}
		}

		return totalFlow;
	}

	int edgeCount(int s)
	{
		return adj[s].size();
	}

	Edge* getEdge(int s, int i)
	{
		return adj[s][i];
	}

private:

	vector<Edge*> adj[Size];
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
				if (level[e->end] != -1 || e->remain() <= 0)
					continue;

				level[e->end] = level[now] + 1;
				q.push(e->end);
			}
		}

		return level[sink] != -1;
	}

	i64 dfs(int s, int e, i64 f)
	{
		if (s == e)
			return f;

		for (int& i = work[s]; i < adj[s].size(); i++)
		{
			auto& next = adj[s][i];

			if (level[next->end] != level[s] + 1 || next->remain() <= 0)
				continue;

			i64 df = dfs(next->end, e, min(f, next->remain()));

			if (df != 0)
			{
				next->addFlow(df);
				return df;
			}
		}

		return 0;
	}
};