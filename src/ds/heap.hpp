#ifndef __DS_HEAP_HPP__
#define __DS_HEAP_HPP__

#include <bits/stdc++.h>

template< typename ElementType,typename Comp=std::greater<ElementType> >
class Heap{
private:
    std :: vector<ElementType> a;
public:
    typedef typename std :: vector<ElementType> :: iterator iterator;
    typedef typename std :: vector<ElementType> :: reverse_iterator reverse_iterator;
    ElementType top(){
        return *a.begin();
    }
    void pop(){
        pop_heap(a.begin(),a.end(),Comp());
        a.pop_back();
    }
    void push(const ElementType& pp){
        a.push_back(pp);
        push_heap(a.begin(),a.end(),Comp());
    }
    iterator begin(){
        return a.begin();
    }
    iterator end(){
        return a.end();
    }
    reverse_iterator rbegin(){
        return a.rbegin();
    }
    reverse_iterator rend(){
        return a.rend();
    }
};
#endif
