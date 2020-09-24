// key based normal splay tree
template<typename T, typename cmp = less<T>>
class SplayTree
{
public:
    void insert(T key)
    {
        sz++;

        if (root == nullptr)
        {
            root = new Node(key);
            return;
        }

        root = root->insert(key);
    }

    bool find(T key)
    {
        if (root == nullptr)
            return false;

        root = root->find(key);
        return root->key == key;
    }

    bool erase(T key)
    {
        if (root == nullptr)
            return false;

        root = root->find(key);
        if (root->key != key)
            return false;

        sz--;
        root = root->erase();
        return true;
    }

    int size() const
    {
        return sz;
    }

    T find_nth(int n)
    {
        root = root->find_nth(n);
        return root->key;
    }

    void clear()
    {
        while (root != nullptr)
            root = root->erase();
    }

    ~SplayTree()
    {
        clear();
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
        Node(T k) : key(k)
        {
        }

        Node* l = nullptr;
        Node* r = nullptr;
        Node* p = nullptr;
        T key;
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

        void update()
        {
            cnt = 1;
            if (l != nullptr) cnt += l->cnt;
            if (r != nullptr) cnt += r->cnt;
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

        Node* insert(T k)
        {
            if (k == key)
            {
                splay();
                return this;
            }

            if (cmp()(k, key))
            {
                if (l == nullptr)
                    set_left(new Node(k));

                return l->insert(k);
            }

            if (r == nullptr)
                set_right(new Node(k));

            return r->insert(k);
        }

        Node* find(T k)
        {
            if (k == key)
            {
                splay();
                return this;
            }

            if (cmp()(k, key))
            {
                if (l == nullptr)
                {
                    splay();
                    return this;
                }

                return l->find(k);
            }

            if (r == nullptr)
            {
                splay();
                return this;
            }

            return r->find(k);
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

        Node* erase()
        {
            if (l != nullptr && r != nullptr)
            {
                l->p = nullptr;
                Node* rp = l;
                while (rp->r != nullptr) rp = rp->r;
                rp->set_right(r);
                rp->splay();
                delete this;
                return rp;
            }

            auto nxt = (l == nullptr) ? r : l;
            delete this;

            if (nxt != nullptr)
                nxt->p = nullptr;

            return nxt;
        }
    };

    Node* root = nullptr;
    int sz = 0;
};