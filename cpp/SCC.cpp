std::vector<int> edges[10001];
bool visited[10001]; // scc에 이미 포함된 경우 true
int discover[10001];
std::stack<int> s;
std::vector<std::vector<int>> scc;
int idx = 1;

int dfs(int k)
{
    s.push(k);

    discover[k] = idx++;

    int ret = discover[k];

    for (auto& edge : edges[k])
    {
        if (visited[edge])
            continue;

        if (discover[edge] != 0)
        {
            ret = std::min(discover[edge], ret);
            continue;
        }

        ret = std::min(dfs(edge), ret);
    }

    if (discover[k] == ret)
    {
        std::vector<int> newScc;

        while (true)
        {
            int t = s.top();
            s.pop();

            visited[t] = true;
            newScc.push_back(t);

            if (t == k)
                break;
        }

        std::sort(newScc.begin(), newScc.end());

        scc.push_back(newScc);
    }

    return ret;
}

void calc_scc()
{
    for (int i = 1; i <= v; i++)
    {
        if (!visited[i])
            dfs(i);
    }

    std::sort(scc.begin(), scc.end(), [](const std::vector<int>& l, const std::vector<int>& r)
    {
        return l[0] < r[0];
    });
}