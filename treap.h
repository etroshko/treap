#ifndef TREAP_H_INCLUDED
#define TREAP_H_INCLUDED

class Node
{
    friend class Treap;
    int key, prior;
    Node *l, *r;
    Node() {}
    Node(int key, int prior):
        key(key), prior(prior), l(0), r(0) { }

};

class Treap
{
private:
    Node *root;
    void insert(Node *t, int key, int prior);
    void copy(Node *&t, Node *org);
    Node* merge(Node *a,Node *b);
    void split(Node *t, int key, Node *&l, Node *&r);
    void destroy(Node *t);
    bool search(Node *t, int key);
    void bypass(Node *t);
    void print (Node *t, int level);
    void unite(Node *&a, Node *&b);
    void intersect(Treap &a, Treap &b, Node *t);
    Treap difference(Treap &t, Node *a,Node *b);
public:
    Treap();
    ~Treap();
    Treap(const Treap &org);
    Treap &operator=(const Treap &org);
    Treap operator+(const Treap &org);
    Treap operator-(const Treap &org);
    Treap operator^(Treap &org);
    void insert(int key, int prior);
    bool search(int key);
    void print();
    void bypass();
};

#endif // TREAP_H_INCLUDED
