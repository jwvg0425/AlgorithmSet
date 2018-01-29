template<int V>
class MCMF
{
public:
    int capa[V][V];
    int cost[V][V];
    int flow[V][V];
    vector<int> adj[V];
    int prev[V], dist[V];
    bool inQ[V];

    void add_edge(int u, int v, int ecapa, int ecost)
    {
        capa[u][v] = ecapa;
        cost[u][v] = ecost;
        cost[v][u] = -ecost;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ii mcmf(int start, int end)
    {
        int min_cost = 0;
        int max_flow = 0;

        while (true)
        {
            spfa(start, end);
            if (prev[end] == -1)
                break;

            int now_flow = INF;

            for (int i = end; i != start; i = prev[i])
                now_flow = min(now_flow, capa[prev[i]][i] - flow[prev[i]][i]);

            for (int i = end; i != start; i = prev[i])
            {
                min_cost += now_flow * cost[prev[i]][i];
                flow[prev[i]][i] += now_flow;
                flow[i][prev[i]] -= now_flow;
            }

            max_flow += now_flow;
        }

        return ii(min_cost, max_flow);
    }

    void spfa(int start, int end)
    {
        queue<int> q;
        fill(inQ, inQ + V, false);
        fill(prev, prev + V, -1);
        fill(dist, dist + V, INF);
        dist[start] = 0;
        inQ[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            inQ[now] = false;

            for (auto& next : adj[now])
            {
                if (capa[now][next] - flow[now][next] > 0 &&
                    dist[next] > dist[now] + cost[now][next])
                {
                    dist[next] = dist[now] + cost[now][next];
                    prev[next] = now;
                    if (!inQ[next])
                    {
                        q.push(next);
                        inQ[next] = true;
                    }
                }
            }
        }
    }

private:
    const int INF = 1 << 30;
};