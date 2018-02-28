vector<int> z_algorithm(const string& str)
{
    vector<int> z;
    z.resize(str.size(), 0);
    int l = 0, r = 0;

    for (int i = 1; i < str.size(); i++)
    {
        if (i > r)
        {
            l = r = i;
            while (r < str.size() && str[r - l] == str[r])
                r++;

            z[i] = r - l;
            r--;
        }
        else
        {
            int k = i - l;
            if (z[k] < r - i + 1)
            {
                z[i] = z[k];
            }
            else
            {
                l = i;
                while (r < str.size() && str[r - l] == str[r])
                    r++;

                z[i] = r - l;
                r--;
            }
        }
    }

    return z;
}