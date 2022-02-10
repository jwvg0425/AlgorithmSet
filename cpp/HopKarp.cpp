template<int Size>
class HopKarp
{
public:
    HopKarp() : n(0)
    {
    }

    void set_size(int n_)
    {
        n = n_;
    }

    void add_edge(int s, int e)
    {
        adj[s].push_back(e);
        rev[e].push_back(s);
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

    vector<int> alternating(const vector<int>& s)
    {
        vector<int> res;
        bool vis[Size][2] = { false, };

        queue<ii> q;

        for (auto& si : s)
        {
            q.emplace(si, 0);
            q.emplace(si, 1);
            vis[si][0] = vis[si][1] = true;
        }

        while (!q.empty())
        {
            auto [now, pmatch] = q.front();
            q.pop();

            auto& cand = adj[now].empty() ? rev[now] : adj[now];

            for (auto& nxt : cand)
            {
                bool matchedEdge = nxt == a[now] || nxt == b[now];
                if (vis[nxt][matchedEdge])
                    continue;

                if (pmatch == matchedEdge)
                    continue;

                vis[nxt][matchedEdge] = true;
                q.emplace(nxt, matchedEdge);
            }
        }

        for (int i = 0; i < n; i++)
            if (vis[i][0] || vis[i][1])
                res.push_back(i);

        return res;
    }

    vector<int> vertex_cover()
    {
        vector<int> st;

        bool inL[Size] = { false, }, inR[Size] = { false, }, inX[Size] = { false, }, inY[Size] = { false, };
        for (int i = 0; i < n; i++)
        {
            if (!adj[i].empty())
            {
                inL[i] = true;
                if (a[i] == -1)
                    st.push_back(i);
            }
            else
            {
                inR[i] = true;
            }
        }

        auto x = alternating(st);

        vector<int> res;

        for (auto& xi : x)
            inX[xi] = true;

        for (int i = 0; i < n; i++)
        {
            if ((inL[i] && !inX[i]) || (inR[i] && inX[i]))
                res.push_back(i);
        }

        return res;
    }

    vector<int> independent_set()
    {
        auto c = vertex_cover();
        int isCover[Size] = { false, };

        for (auto& ci : c)
            isCover[ci] = true;

        vector<int> res;

        for (int i = 0; i < n; i++)
            if (!isCover[i])
                res.push_back(i);

        return res;
    }

    int a[Size], b[Size];

private:
    const int INF = 1 << 30;
    int n;
    int dist[Size] = { 0, };
    bool used[Size] = { false, };
    vector<int> adj[Size];
    vector<int> rev[Size];
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