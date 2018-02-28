constexpr int clog2(int n)
{
    return ((n < 2) ? 1 : 1 + clog2(n / 2));
}

template<typename T, int MAXN>
class Tree
{
public:
    Tree() : n(MAXN)
    {
        memset(parent, -1, sizeof(parent));
        memset(depth, -1, sizeof(depth));
    }

    void set_size(int n_)
    {
        assert(!is_init);
        assert(n_ < MAXN);
        n = n_;
    }

    void add_edge(int u, int v, T val = T())
    {
        assert(!is_init);
        adj[u].emplace_back(v, val);
        adj[v].emplace_back(u, val);
    }

    virtual void init(int root)
    {
        assert(!is_init);
        is_init = true;
        depth[root] = 0;
        make_tree(root);

        for (int j = 0; j < K; j++)
            for (int i = 0; i <= n; i++)
                if (parent[i][j] != -1)
                    parent[i][j + 1] = parent[parent[i][j]][j];
    }

    int lca(int u, int v)
    {
        assert(is_init);

        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; diff > 0; j++)
        {
            if (diff % 2 == 1)
                u = parent[u][j];

            diff /= 2;
        }

        if (u != v)
        {
            for (int j = K - 1; j >= 0; j--)
            {
                if (parent[u][j] != -1 &&
                    parent[u][j] != parent[v][j])
                {
                    u = parent[u][j];
                    v = parent[v][j];
                }
            }
            u = parent[u][0];
        }

        return u;
    }

protected:
    const int K = clog2(MAXN) + 1;
    bool is_init = false;
    int n;
    int root;
    int parent[MAXN][clog2(MAXN) + 2];
    int depth[MAXN];
    T value[MAXN];
    vector<int> children[MAXN];
    vector<pair<int, T>> adj[MAXN];

    void make_tree(int root)
    {
        for (ii a : adj[root])
        {
            int next = a.first;
            int v = a.second;

            if (depth[next] == -1)
            {
                parent[next][0] = root;
                children[root].push_back(next);
                value[next] = v;
                depth[next] = depth[root] + 1;
                make_tree(next);
            }
        }
    }
};