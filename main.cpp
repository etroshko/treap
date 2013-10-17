#include <iostream>
#include <cstdlib>
#include <ctime>
#include "treap.h"

using namespace std;

int main()
{
    srand(time(0));
    Treap a, b, c;
    int key, prior, element, n, m;
    cout<<"Number of elements of treap a"<<endl;
    cin>>n;
    for(int i=0; i<n; ++i)
    {
        prior=rand()%50;
        cout<<i+1<<". ";
        cin>>key;
        a.insert(key, prior);
    }
    cout<<endl;
    a.print();
    cout<<endl;
    cout<<"Element to find"<<endl;
    cin>>element;
    cout<<(a.search(element)?'+':'-');
    cout<<endl;
    cout<<"Number of elements of treap b"<<endl;
    cin>>m;
    for(int i=0; i<m; ++i)
    {
        prior=rand()%50;
        cout<<i+1<<". ";
        cin>>key;
        b.insert(key, prior);
    }
    cout<<endl;
    b.print();
    cout<<endl;
    cout<<"Element to find"<<endl;
    cin>>element;
    cout<<(b.search(element)?'+':'-');
    cout<<endl<<"Union:\n";
    (a+b).print();
    cout<<endl<<"Difference:\n";
    (a-b).print();
    cout<<endl<<"Intersection:\n";
    (a^b).print();
    cout<<endl;
      return 0;

}
