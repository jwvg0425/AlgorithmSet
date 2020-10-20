template<int Size>
class HorpKarp
{
public:
    HorpKarp() : n(0)
    {
    }

    void set_size(int n_)
    {
        n = n_;
    }

    void add_edge(int s, int e)
    {
        adj[s].push_back(e);
    }

    int matching()
    {
        int res = 0;
        memset(a, -1, sizeof(a));
        memset(b, -1, sizeof(b));

        while (true)
        {
            bfs();
            memset(work, 0, sizeof(work));

            int flow = 0;
            for (int i = 0; i <= n; i++)
                if (!used[i] && dfs(i))
                    flow++;

            if (flow == 0)
                break;

            res += flow;
        }

        return res;
    }

    int a[Size], b[Size];

private:
    const int INF = 1 << 30;
    int n;
    int dist[Size];
    bool used[Size];
    vector<int> adj[Size];
    int work[Size] = { 0, };

    void bfs()
    {
        queue<int> q;

        for (int i = 0; i <= n; i++)
        {
            if (!used[i])
            {
                dist[i] = 0;
                q.push(i);
                continue;
            }

            dist[i] = INF;
        }

        while (!q.empty())
        {
            int s = q.front();
            q.pop();
            for (int e : adj[s])
            {
                if (b[e] != -1 && dist[b[e]] == INF)
                {
                    dist[b[e]] = dist[s] + 1;
                    q.push(b[e]);
                }
            }
        }
    }

    bool dfs(int s)
    {
        for (int& i = work[s]; i < adj[s].size(); i++)
        {
            auto e = adj[s][i];
            if (b[e] == -1 || (dist[b[e]] == dist[s] + 1 && dfs(b[e])))
            {
                used[s] = true;
                a[s] = e;
                b[e] = s;
                return true;
            }
        }

        return false;
    }
};