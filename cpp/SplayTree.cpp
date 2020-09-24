template<typename T>
class SplayTree
{
public:
    void insert(T key)
    {
        Node* now = root;

        if (root == nullptr)
        {
            root = create(key);
            return;
        }

        while (true)
        {
            if (key == now->key)
                return;

            if (key < now->key)
            {
                if (now->left == nullptr)
                {
                    auto added = create(key);
                    now->set_left(added);
                    splay(added);
                    break;
                }

                now = now->left;
            }
            else
            {
                if (now->right == nullptr)
                {
                    auto added = create(key);
                    now->set_right(added);
                    splay(added);
                    break;
                }

                now = now->right;
            }
        }
    }

    bool find(T key)
    {
        Node* now = root;

        if (root == nullptr)
            return false;

        while (true)
        {
            if (key == now->key)
                break;

            if (key < now->key)
            {
                if (now->left == nullptr)
                    break;

                now = now->left;
            }
            else
            {
                if (now->right == nullptr)
                    break;

                now = now->right;
            }
        }

        splay(now);
        return key == now->key;
    }

    void erase(T key)
    {
        if (!find(key))
            return;

        Node* pre = root;

        if (pre->left != nullptr)
        {
            if (pre->right != nullptr)
            {
                root = pre->left;
                root->parent = nullptr;
                Node* rp = root;
                while (rp->right != nullptr)
                    rp = rp->right;

                rp->set_right(pre->right);
                splay(rp);
                delete pre;
                return;
            }

            root = pre->left;
            root->parent = nullptr;
            delete pre;
            return;
        }

        if (pre->right != nullptr)
        {
            root = pre->right;
            root->parent = nullptr;
            delete pre;
            return;
        }

        delete pre;
        root = nullptr;
    }

    void clear()
    {
        while (root != nullptr)
            erase(root->key);
    }

    ~SplayTree()
    {
        clear();
    }

private:
    struct Node
    {
        Node(T k) : key(k)
        {
        }

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        T key;

        void set_left(Node* n)
        {
            left = n;
            if (n != nullptr)
                n->parent = this;
        }

        void set_right(Node* n)
        {
            right = n;
            if (n != nullptr)
                n->parent = this;
        }
    };

    Node* root = nullptr;

    Node* create(T k)
    {
        auto node = new Node(k);
        return node;
    }

    void rotate(Node* node)
    {
        Node* p = node->parent;
        Node* g = p->parent;
        if (g != nullptr)
        {
            if (g->left == p)
                g->set_left(node);
            else
                g->set_right(node);
        }
        else
        {
            node->parent = nullptr;
            root = node;
        }

        if (node == p->left)
        {
            Node* r = node->right;
            p->set_left(r);
            node->set_right(p);
        }
        else
        {
            Node* l = node->left;
            p->set_right(l);
            node->set_left(p);
        }
    }

    void splay(Node* node)
    {
        while (node->parent != nullptr)
        {
            Node* p = node->parent;
            Node* g = p->parent;
            if (g != nullptr)
            {
                if ((node == p->left) == (p == g->left))
                    rotate(p);
                else
                    rotate(node);
            }

            rotate(node);
        }
    }
};