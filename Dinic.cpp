struct Edge
{
	int end, capa, flow;
	Edge* dual;

	Edge() : Edge(-1, 0) {}
	Edge(int e, int c) : end(e), capa(c), flow(0), dual(nullptr) {}

	int remain()
	{
		return capa - flow;
	}

	void addFlow(int f)
	{
		flow += f;
		dual->flow -= f;
	}
};

template<int Size>
class Dinic
{
public:
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

	//a,b간에 capacity c인 엣지 추가
	Edge* addEdge(int a, int b, int c)
	{
		auto e1 = new Edge(b, c);
		auto e2 = new Edge(a, 0);
		e1->dual = e2;
		e2->dual = e1;

		adj[a].push_back(e1);
		adj[b].push_back(e2);

		return e1;
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

	int dfs(int s, int e, int f)
	{
		if (s == e)
			return f;

		for (int& i = work[s]; i < adj[s].size(); i++)
		{
			auto& next = adj[s][i];

			if (level[next->end] != level[s] + 1 || next->remain() <= 0)
				continue;

			int df = dfs(next->end, e, std::min(f, next->remain()));

			if (df != 0)
			{
				next->addFlow(df);
				return df;
			}
		}

		return 0;
	}
};
