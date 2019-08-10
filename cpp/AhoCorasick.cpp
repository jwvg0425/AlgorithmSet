class AhoCorasick
{
public:
    struct Node
    {
        Node() : matched(0), fail(0)
        {
            memset(next, -1, sizeof(next));
        }

        int next[26];
        int matched;
        int fail;
    };

    class Matcher
    {
    public:
        Matcher(const AhoCorasick& ac_) : ac(ac_), now(0)
        {
        }

        int matched() const
        {
            return ac.getNode(now).matched;
        }

        void move(char c)
        {
            int v = now;

            while (v != 0 && ac.getNode(v).next[c - 'a'] == -1)
                v = ac.getNode(v).fail;

            if (ac.getNode(v).next[c - 'a'] != -1)
                v = ac.getNode(v).next[c - 'a'];

            now = v;
        }

    private:
        int now;
        const AhoCorasick& ac;
    };

    AhoCorasick()
    {
        nodes.emplace_back();
    }

    void build(const vector<string>& patterns)
    {
        for (auto& p : patterns)
            insert(0, p, 0);

        bfs();
    }

    Node getNode(int idx) const
    {
        return nodes[idx];
    }

    Matcher match() const
    {
        return Matcher(*this);
    }

private:
    void insert(int vertex, const string& pattern, int idx)
    {
        if (idx == pattern.size())
        {
            nodes[vertex].matched++;
            return;
        }

        if (nodes[vertex].next[pattern[idx] - 'a'] == -1)
        {
            nodes.emplace_back();
            nodes[vertex].next[pattern[idx] - 'a'] = nodes.size() - 1;
        }

        insert(nodes[vertex].next[pattern[idx] - 'a'], pattern, idx + 1);
    }

    void bfs()
    {
        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            auto now = q.front();
            q.pop();

            for (int i = 0; i < 26; i++)
            {
                if (nodes[now].next[i] == -1)
                    continue;

                int next = nodes[now].next[i];
                q.push(next);

                int p = now;

                if (p == 0)
                {
                    nodes[next].fail = p;
                    continue;
                }

                p = nodes[now].fail;

                while (p != 0 && nodes[p].next[i] == -1)
                    p = nodes[p].fail;

                if (nodes[p].next[i] != -1)
                    p = nodes[p].next[i];

                nodes[next].fail = p;
                nodes[next].matched += nodes[p].matched;
            }
        }
    }

    vector<Node> nodes;
};
