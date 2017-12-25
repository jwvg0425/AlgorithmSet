constexpr int clog2(int n)
{
    return ((n < 2) ? 1 : 1 + clog2(n / 2));
}

template<int MAXN>
class Tree
{
public:
    Tree()
    {
        memset(parent, -1, sizeof(parent));
        memset(depth, -1, sizeof(depth));
    }

    void set_size(int n_)
    {
        n = n_;
    }

    void add_edge(int a, int b)
    {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void init(int root)
    {
        depth[root] = 0;
        make_tree(root);

        for (int j = 0; j < K; j++)
            for (int i = 0; i <= n; i++)
                if (parent[i][j] != -1)
                    parent[i][j + 1] = parent[parent[i][j]][j];
    }

    int lca(int a, int b)
    {
        if (depth[a] < depth[b])
            swap(a, b);

        int diff = depth[a] - depth[b];

        for (int j = 0; diff; j++)
        {
            if (diff % 2 == 1)
                a = parent[a][j];
            diff /= 2;
        }

        if (a != b)
        {
            for (int j = K - 1; j >= 0; j--)
            {
                if (parent[a][j] != -1 &&
                    parent[a][j] != parent[b][j])
                {
                    a = parent[a][j];
                    b = parent[b][j];
                }
            }
            a = parent[a][0];
        }

        return a;
    }

private:
    int n;
    int root;
    int K = clog2(MAXN) + 1;
    int parent[MAXN][clog2(MAXN) + 2];
    int depth[MAXN];
    vector<int> child[MAXN];
    vector<int> adj[MAXN];

    void make_tree(int root)
    {
        for (int next : adj[root])
        {
            if (depth[next] == -1)
            {
                parent[next][0] = root;
                depth[next] = depth[root] + 1;
                make_tree(next);
            }
        }
    }
};