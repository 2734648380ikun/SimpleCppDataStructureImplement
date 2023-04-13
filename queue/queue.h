#ifndef _QUEUE_XIE
#define _QUEUE_XIE
#include<memory>
#include"../link/list.h"
#include"../link/list.cpp"
namespace xie
{
    template<class T>
    class queue
    {
        using link_ptr=xie::link<T>*;
    private:
        link_ptr head;
        link_ptr tail;
    public:
        queue():head(nullptr),tail(nullptr){}
        queue(const queue<T>& q)=delete;
        queue<T>& operator=(const queue<T>& q)=delete;
        queue(const queue<T>&& q):head(std::move(q.head)),tail(std::move(q.tail)){}
        queue<T>& operator=(const queue<T>&&q){
            tail=q.tail;
            head=q.head;
        }
        ~queue();
        void enqueue(const T& value); // —— 在可容的情况下添加元素到尾部
        T dequeue(); // —— 删除最早添加的元素并返回其值
        bool empty()const{return head==nullptr;}
        void full(const size_t& num,const T& value); // —— 填充队列 
    };
    
} // namespace xie
#endif