
// dependency : SegmentTree.cpp
template<typename T, int SZ>
class HLD
{
public:
    template<typename M>
    HLD(const M& m) : merge(m), tree(m)
    {
        memset(in, -1, sizeof(in));
    }

    void add_edge(int x, int y)
    {
        edge[x].push_back(y);
        edge[y].push_back(x);
    }

    void init(int root, const vector<T>& raw)
    {
        t = 1;
        in[0] = 0;
        depth[root] = 1;
        dfs_sz(root);
        dfs_hld(root);

        vector<T> changed(raw.size());

        for (int i = root; i < raw.size(); i++)
        {
            if (in[i] == -1)
                continue;

            changed[in[i]] = raw[i];
        }

        tree.init(changed);
    }

    void update(int idx, const T& val)
    {
        tree.update(in[idx], val);
    }

    T query_path(int u, int v)
    {
        if (depth[u] > depth[v])
            swap(u, v);

        if (top[u] == top[v])
            return tree.query(in[u], in[v]);

        if (depth[top[u]] > depth[top[v]])
            swap(u, v);

        return merge(tree.query(in[top[v]], in[v]), query_path(par[top[v]], u));
    }

    T query_subtree(int u)
    {
        return tree.query(in[u], out[u]);
    }

private:
    void dfs_sz(int root)
    {
        sz[root] = 1;
        for (auto& e : edge[root])
        {
            edge[e].erase(find(all(edge[e]), root));
            depth[e] = depth[root] + 1;
            par[e] = root;
            dfs_sz(e);
            sz[root] += sz[e];

            if (sz[e] > sz[edge[root][0]])
                swap(e, edge[root][0]);
        }
    }

    void dfs_hld(int root)
    {
        in[root] = t++;
        for (auto& e : edge[root])
        {
            if (e == edge[root][0])
                top[e] = top[root];
            else
                top[e] = e;

            dfs_hld(e);
        }

        out[root] = t;
    }

    SegmentTree<T> tree;
    using Merge = function<T(const T&, const T&)>;
    Merge merge;

    vector<int> edge[SZ];
    int t = 1;
    int sz[SZ];
    int in[SZ];
    int out[SZ];
    int top[SZ];
    int par[SZ];
    int depth[SZ];
};
