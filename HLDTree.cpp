template<typename T, int MAXN>
class HLDTree : public Tree<T, MAXN>
{
    using MergeFunc = function<T(T, T)>;
public:
    HLDTree(const MergeFunc& seg_func)
        : seg_merge(seg_func), merge(seg_func) {}

    HLDTree(const MergeFunc& seg_func,
        const MergeFunc& merge_func)
        : seg_merge(seg_func), merge(merge_func) {}

    virtual void init(int root) override
    {
        Tree<T, MAXN>::init(root);
        calc_subtree(root);
        heavy_light_decomposition(root);
        init_trees();
    }

    void update(int u, int v, const T& val)
    {
        assert(this->is_init);

        if (this->parent[u][0] == v)
            swap(u, v);

        assert(this->parent[v][0] == u);

        int path = heavy_path_index[v];
        int index = find_edge(path, v);

        segment_trees[path].update(index, val);
    }

    T query(int u, int v)
    {
        assert(u != v);
        int common = this->lca(u, v);

        if (common == u)
            return query_topdown(common, v);

        if (common == v)
            return query_topdown(common, u);

        return merge(query_topdown(common, u), query_topdown(common, v));
    }

protected:
    T query_topdown(int u, int v)
    {
        if (heavy_path_index[u] == heavy_path_index[v])
        {
            int path = heavy_path_index[u];
            int first = find_edge(path, u) + 1;
            int last = find_edge(path, v);
            return segment_trees[path].query(first, last);
        }

        int path = heavy_path_index[v];
        int top = heavy_paths[path][0];

        assert(top != v);

        int last = find_edge(path, v);

        if (u == top)
            return segment_trees[path].query(0, last);

        return max(query_topdown(u, top),
            segment_trees[path].query(0, last));
    }

    int find_edge(int path_index, int v)
    {
        int top_of_path = heavy_paths[path_index][0];
        return this->depth[this->parent[v][0]] - this->depth[top_of_path];
    }

    void calc_subtree(int root)
    {
        subtree_size[root] = 1;

        for (int child : this->children[root])
        {
            calc_subtree(child);
            subtree_size[root] += subtree_size[child];
        }
    }

    void heavy_light_decomposition(int root)
    {
        assert(this->is_init);
        heavy_paths.clear();
        heavy_path_index.resize(this->n + 1, -1);

        queue<int> q;
        q.push(root);

        while (!q.empty())
        {
            int here = q.front();
            q.pop();

            for (auto& child : this->children[here])
                q.push(child);

            if (here == root)
                continue;

            int p = this->parent[here][0];

            if (subtree_size[here] * 2 >= subtree_size[p] &&
                p != root)
            {
                int parent_path_index = heavy_path_index[p];
                heavy_paths[parent_path_index].push_back(here);
                heavy_path_index[here] = parent_path_index;
            }
            else
            {
                heavy_path_index[here] = heavy_paths.size();
                heavy_paths.push_back(vector<int>(2));
                heavy_paths.back()[0] = p;
                heavy_paths.back()[1] = here;
            }
        }
    }

    void init_trees()
    {
        segment_trees.clear();
        segment_trees.reserve(heavy_paths.size());

        for (const auto& path : heavy_paths)
        {
            int m = path.size();
            vector<int> values;

            for (int i = 1; i < m; i++)
                values.push_back(this->value[path[i]]);

            segment_trees.emplace_back(values, seg_merge);
        }
    }

    int subtree_size[MAXN];
    vector<vector<int>> heavy_paths;
    vector<int> heavy_path_index;
    vector<SegmentTree<int>> segment_trees;

    MergeFunc seg_merge;
    MergeFunc merge;
};