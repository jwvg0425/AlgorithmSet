#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#define all(x) (x).begin(), (x).end()
#define xx first
#define yy second

using namespace std;

template<typename T, typename Pr = less<T>>
using pq = priority_queue<T, vector<T>, Pr>;
using i64 = long long int;
using ii = pair<int, int>;
using ii64 = pair<i64, i64>;

constexpr int clog2(int n) { return ((n < 2) ? 1 : 1 + clog2(n / 2)); }

template<typename T>
class SegmentTree
{
public:
    template<typename M>
    SegmentTree(const M& m) : merge(m) {}

    void init(vector<T>& raw_)
    {
        raw = raw_;
        n = (int)raw.size();
        int sz = (1 << (clog2(n) + 1));
        data.resize(sz);

        _init(raw, 1, 0, n - 1);
    }

    T modify(int idx, function<T(T)> modifier) { return update(idx, modifier(raw[idx])); }
    T update(int idx, const T& newVal) { raw[idx] = newVal; return _update(1, 0, n - 1, idx, newVal); }
    T query(int left, int right) { return _query(1, 0, n - 1, left, right); }

private:
    vector<T> raw;
    vector<T> data;
    int n;
    using Merge = function<T(const T&, const T&)>;
    Merge merge;

    T _init(vector<T>& raw, int node, int start, int end)
    {
        int mid = (start + end) / 2;
        if (start == end)
            return data[node] = raw[start];
        else
            return data[node] = merge(_init(raw, node * 2, start, mid),
                _init(raw, node * 2 + 1, mid + 1, end));
    }

    T _update(int node, int start, int end, int index, const T& newVal)
    {
        if (index < start || index > end)
            return data[node];

        if (start == end)
            data[node] = newVal;
        else
        {
            int mid = (start + end) / 2;
            data[node] = merge(_update(node * 2, start, mid, index, newVal),
                _update(node * 2 + 1, mid + 1, end, index, newVal));
        }

        return data[node];
    }

    T _query(int node, int start, int end, int left, int right)
    {
        if (left <= start && end <= right)
            return data[node];

        int mid = (start + end) / 2;

        if (mid < left)
            return _query(node * 2 + 1, mid + 1, end, left, right);

        if (mid + 1 > right)
            return _query(node * 2, start, mid, left, right);

        return merge(_query(node * 2, start, mid, left, right),
            _query(node * 2 + 1, mid + 1, end, left, right));
    }
};


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
