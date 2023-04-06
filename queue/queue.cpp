#include"./queue.h"
namespace xie
{
    template<class T>
    queue<T>::~queue(){
        while(head!=nullptr){
            link<T>*t=head;
            head=head->next;
            delete t;
        }
    }
    template<class T>
    inline void queue<T>::enqueue(const T& value){
        if(head==nullptr){
            head=new link<T>(value);
            tail=head;
        }else{
            tail->next=new link<T>(value);
            tail=tail->next;
        }
        
    }
    template<class T>
    inline T queue<T>::dequeue(){
        T value;
        if(head!=nullptr){
            link_ptr t=head->next;
            value=head->data;
            delete head;
            head=t;
        }
        return value;
    }
    template<class T>
    inline void queue<T>::full(const size_t& num,const T& value){
        for(size_t i=0;i<num;++i){
            enqueue(value);
        }
    }

} // namespace name