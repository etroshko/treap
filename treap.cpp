#include "treap.h"
#include <iostream>

Treap::Treap():
    root(0) {}

Treap::~Treap()
{
    destroy(root);
}

Treap::Treap(const Treap &org)
{
    if (org.root)
    {
        root=new Node(org.root->key, org.root->prior);
        copy(root, org.root);
    }
    else root=0;
}

Treap &Treap::operator=(const Treap &org)
{
    if(this==&org)
        return *this;
    destroy(root);
    copy(root,org.root);
    return *this;
}

Treap Treap::operator+(const Treap &org)
{
    Treap temp=org;
    unite(root, temp.root);
    return *this;
}

Treap Treap::operator-(const Treap &org)
{
    Treap temp;
    if(!this && org.root)
    {
        destroy(temp.root);
        *this=temp;
    }
    else  if(this && !org.root)
        return *this;
    if(this!=&org)
    {
        difference(temp,root,org.root);
        return temp;
    }
    else
        return *this;
}

Treap Treap::operator^(Treap &org)
{
    Treap temp;
    intersect(temp, org, root);
    return temp;
}

void Treap::insert(int key, int prior)
{
    insert(root,key, prior);
}

bool Treap::search(int key)
{
    return search(root, key);
}

void Treap::print()
{
    print(root, 0);
}
void Treap::bypass()
{
    bypass(root);
}

//----------------------------------------------------------------------//

void Treap::insert(Node *t, int key, int prior)
{
    t = new Node(key, prior);
    Node *l, *r;
    if(!search(key))
    {
        split(root, key, l , r);
        root=merge(l,t);
        root=merge(root,r);
    }
}

void Treap::copy(Node *&t, Node *org)
{
    if(!org)
        t=0;
    else
    {
        t=new Node(org->key, org->prior);
        if(org->l)
            copy(t->l,org->l);
        else
            t->l=0;
        if(org->r)
            copy(t->r,org->r);
        else
            t->r=0;
    }
}

Node* Treap::merge(Node *l, Node *r)
{
    if(!l||!r)
        return l?l:r;
    if(l->prior > r->prior)
    {
        l->r=merge(l->r, r);
        return l;
    }
    else
    {
        r->l=merge(l, r->l);
        return r;
    }
}

void Treap::split(Node *t, int key, Node *&l, Node *&r)
{
    if(!t)
        l=r=0;

    else if(key<t->key)
    {
        split(t->l, key, l, t->l);
        r=t;
    }
    else
    {
        split(t->r, key, t->r, r);
        l=t;
    }
}

void Treap::destroy(Node *t)
{
    if(t)
    {
        destroy(t->l);
        destroy(t->r);
        delete t;
        t=0;
    }
}

void Treap::bypass(Node *t)
{
    if(t)
    {
        bypass(t->l);
        std::cout<<t->key<<' ';
        bypass(t->r);
    }
}

bool Treap::search(Node *t, int key)
{
    while(t)
    {
        if (t->key > key)
            t=t->l;
        else if (t->key < key)
            t=t->r;
        else return true;
    }
    return false;
}

void Treap::print(Node *t, int level)
{
    if(t)
    {
        print(t->l, level+1);
        for(int i=0; i<level; i++)
            std::cout<<"...";
        std::cout<<t->key<<std::endl;
        print(t->r,level+1);
    }
}

void Treap::unite(Node *&l, Node *&r)
{
    if(r!=0)
    {
        insert(l,r->key,r->prior);
        unite(l,r->l);
        unite(l,r->r);
    }
}

void Treap::intersect(Treap &a, Treap &b, Node *t)
{
    if(!t) return;
    if(b.search(t->key))
        a.insert(t->key, t->prior);
    intersect(a,b,t->l);
    intersect(a,b,t->r);
}

Treap Treap::difference(Treap &t, Node *a,Node *b)
{
    if(a)
    {
    if(!search(b, a->key))
            t.insert(a->key, a->prior);
        difference(t, a->l, b);
        difference(t, a->r, b);
    }
    return t;
}


