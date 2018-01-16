class SuffixArray
{
public:
    SuffixArray(const string& str)
    {
        constructSA(str);
        constructLCP(str);
    }

    vector<int> sa;
    vector<int> lcp;

private:
    void constructSA(const string& str)
    {
        pos.resize(str.size());
        sa.resize(str.size());

        for (int i = 0; i < str.size(); i++)
        {
            sa[i] = i;
            pos[i] = str[i];
        }

        for (int d = 1;; d *= 2)
        {
            sort(sa.begin(), sa.end(), [this, d](auto& l, auto& r) { return cmp(l, r, d); });
            vector<int> temp(str.size());

            for (int i = 0; i < str.size() - 1; i++)
                temp[i + 1] = temp[i] + cmp(sa[i], sa[i + 1], d);

            for (int i = 0; i < str.size(); i++)
                pos[sa[i]] = temp[i];

            if (temp[str.size() - 1] == str.size() - 1)
                break;
        }
    }

    void constructLCP(const string& str)
    {
        lcp.resize(str.size());

        for (int i = 0, k = 0; i < str.size(); i++, k = max(k - 1, 0))
        {
            if (pos[i] == str.size() - 1)
                continue;

            for (int j = sa[pos[i] + 1]; str[i + k] == str[j + k]; k++);

            lcp[pos[i]] = k;
        }
    }

    bool cmp(int i, int j, int d)
    {
        if (pos[i] != pos[j])
            return pos[i] < pos[j];

        if (i + d < sa.size() && j + d < sa.size())
            return pos[i + d] < pos[j + d];

        return i + d > j + d;
    }

    vector<int> pos;
};