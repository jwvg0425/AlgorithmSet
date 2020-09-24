template<typename T>
class SegSplayTree
{
public:
    template<typename Merge>
    SegSplayTree(int n, Merge m)
    {
        root = new Node(m);
        Node* now = root;
        now->cnt = n;

        for (int i = 1; i < n; i++)
        {
            now->set_right(new Node(m));
            now = now->r;
            now->cnt = n - i;
        }
    }

    void set(int i, const T& val)
    {
        root = root->find_nth(i);
        root->set(val);
    }

    void add(int i, const T& val)
    {
        root = root->find_nth(i);
        root->update(val);
    }

    T query(int l, int r)
    {
        interval(l, r);
        return root->r->l->sum;
    }

    void interval(int l, int r)
    {
        root = root->find_nth(l - 1);
        root->r->p = nullptr;
        root->set_right(root->r->find_nth(r - l + 1));
    }

private:
    struct Node
    {
        using M = function<T(const T&, const T&)>;
        Node(M m) : val(), sum(), merge(m) { }

        Node* l = nullptr;
        Node* r = nullptr;
        Node* p = nullptr;
        M merge;
        T val, sum;
        int cnt = 1;

        void set_left(Node* n)
        {
            l = n;
            if (n != nullptr) n->p = this;
        }

        void set_right(Node* n)
        {
            r = n;
            if (n != nullptr) n->p = this;
        }

        void set(const T& v)
        {
            val = v;
            update();
        }

        void update(const T& v)
        {
            val = merge(val, v);
            sum = merge(sum, v);
        }

        void update()
        {
            cnt = 1;
            sum = val;
            if (l != nullptr)
            {
                cnt += l->cnt;
                sum = merge(sum, l->sum);
            }

            if (r != nullptr)
            {
                cnt += r->cnt;
                sum = merge(sum, r->sum);
            }
        }

        void rotate()
        {
            Node* pp = p;
            Node* g = p->p;
            p = g;
            if (g != nullptr)
            {
                if (g->l == pp)
                    g->set_left(this);
                else
                    g->set_right(this);
            }

            if (this == pp->l)
            {
                pp->set_left(r);
                set_right(pp);
            }
            else
            {
                pp->set_right(l);
                set_left(pp);
            }

            pp->update();
            update();
        }

        void splay()
        {
            while (p != nullptr)
            {
                Node* g = p->p;
                if (g != nullptr)
                {
                    if ((this == p->l) == (p == g->l))
                        p->rotate();
                    else
                        rotate();
                }

                rotate();
            }
        }

        // 0-based
        Node* find_nth(int n)
        {
            if (l != nullptr)
            {
                if (l->cnt > n)
                    return l->find_nth(n);

                n -= l->cnt;
            }

            if (n == 0)
            {
                splay();
                return this;
            }

            if (r == nullptr)
                return nullptr;

            return r->find_nth(n - 1);
        }
    };

    Node* root = nullptr;
};