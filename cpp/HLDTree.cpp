
template<typename T, int SZ>
class HLD
{
public:
    template<typename M>
    HLD(const M& m) : merge(m), tree(m)
    {
    }

    void add_edge(int x, int y)
    {
        edge[x].push_back(y);
        edge[y].push_back(x);
    }

    void init(int root, const vector<T>& raw)
    {
        t = 1;
        dfs_sz(root);
        dfs_hld(root);
        tree.init(raw);
    }

    void update(int idx, const T& val)
    {
        tree.update(idx, val);
    }

    T query_path(int u, int v)
    {

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
            dfs_sz(e);
            sz[root] += sz[e];

            if (sz[e] > sz[edge[root][0]])
                swap(e, sz[root][0]);
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
};
