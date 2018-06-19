template<int N>
class DisjointSet
{
public:
    DisjointSet()
    {
        for (int i = 0; i < N; i++)
            parent[i] = i;
    }

    int find(int u)
    {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v)
    {
        u = find(u);
        v = find(v);

        if (u == v) return;

        parent[u] = v;

        find(v);
    }

private:
    int parent[N + 1];
};