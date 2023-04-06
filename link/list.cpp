#include"list.h"
#include<iostream>
namespace xie
{
    template<class T>
    list<T>::~list(){
        while(head!=nullptr){
            link<T>*t=head;
            head=head->next;
            delete t;
        }
    }
    template<class T>
    inline T& list<T>::at(const size_t& index)const{
        link<T>*t=head;
        for(size_t i=0;i<index;++i){
            if(t!=nullptr) t=t->next;
            else throw "越界！";
        }
        return t->data;
    }
    template<class T>
    inline size_t list<T>::size()const noexcept{
        size_t len=0;
        link<T>*t=head;
        while(t!=nullptr){
            ++len;
            t=t->next;
        }
        return len;
    }
    template<class T>
    inline void list<T>::push_front(const T& value){
        link<T>* t=head;
        head=new link<T>(value,t);
    }
    template<class T>
    inline T list<T>::pop_front(){
        link<T>* t=head;
        T value=t->data;
        if(!t) throw "链表无节点";
        else{
            head=head->next;
            delete t;
        }
        return value;
    }
    template<class T>
    inline void list<T>::push_back(const T& value){
        link<T>* t=head;
        if(t!=nullptr){
            while(t->next!=nullptr){
                t=t->next;
            }
            t->next=new link<T>(value);
       }else{
            push_front(value);
       }
    }
    template<class T>
    inline T list<T>::pop_back(){
        link<T>* t=head;
        link<T>* t1=head;
        while(t&&t->next!=nullptr){
            t1=t;
            t=t->next;
        }
        return t1->data;
    }
    template<class T>
    inline T& list<T>::back()const{
        link<T>* t=head;
        while(t&&t->next!=nullptr){
            t=t->next;
        }
        return t->data;
    }
    template<class T>
    inline link<T>* list<T>::find(const size_t& index)const{
        link<T>* t=head;
        for(size_t i=0;i<index;++i){
            if(!t->next) return nullptr;
            t=t->next;
        }
        return t;
    }
    template<class T>
    inline bool list<T>::insert(const size_t& index,const T& value){
        link<T>* t=head;
        if(index==0) push_front(value);
        else{
            t=find(index-1);
            if(!t) return false;
            link<T>* t1=t->next;
            t->next=new link<T>(value);
            t->next->next=t1;
        }
        return true;
    }
    template<class T>
    inline bool list<T>::erase(const size_t& index){
        link<T>* t=head;
        if(index==0) pop_front();
        else{
            t=find(index-1);
            if(t==nullptr||t->next==nullptr) return false;
            link<T>* t1=t->next;
            if(t1){
                t->next=t1->next;
                delete t1;
            } 
        }
        return true;
    }
    template<class T>
    inline void list<T>::reverse(){
        link<T>* t=head;
        if(t!=nullptr&&t->next!=nullptr){
            link<T>*t1=t->next;
            while(t1!=nullptr){
                link<T>*t2=t1->next;
                t1->next=t;
                t=t1;
                t1=t2;
            }
            head->next=nullptr;
            head=t;
        }
    }
    template<class T>
    inline size_t list<T>::value_n_from_end(const size_t& index)const{
        return at(size()-index-1);
    }
    template<class T>
    inline bool list<T>::remove_value(const T& value){
        link<T>* t=head;
        while(t!=nullptr){
            if(t->data==value){
                erase(i);
                return true;
            }
            t=t->next;
        }
        return false;
    }
} // namespace xie
