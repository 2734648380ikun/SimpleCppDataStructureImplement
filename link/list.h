#ifndef _LIST_XIE
#define _LIST_XIE
#include<memory>
namespace xie
{
    template<class T>
    struct link
    {
        T data;
        link<T>* next;
        link():next(nullptr){}
        link(const T& value):data(value),next(nullptr){}
        link(link<T>* l):next(l){}
        link(const T& value,link<T>*l):data(value),next(l){}
        link(const link<T>&& l)noexcept:data(std::move(l.data)),next(std::move(l.next)){}
    };
    template<class T>
    class list
    {
    private:
        link<T>* head;
    public:
        explicit list():head(nullptr){}
        list(const link<T>* lk):head(new link<T>()){}
        list(const list<T>& l)=delete;
        list& operator=(const list& l)=delete;
        list(const list<T>&& l)noexcept:head(l.head){}
        T& operator[](const size_t& index)const{return at(index);}
        ~list();
        size_t size()const noexcept;
        bool empty()const noexcept{return size()==0;}
        link<T>* find(const size_t& index)const;
        T& at(const size_t& index)const;
        void push_front(const T& value);// —— 添加元素到链表的首部
        T pop_front();// —— 删除首部元素并返回其值
        void push_back(const T& value);// —— 添加元素到链表的尾部
        T pop_back();// —— 删除尾部元素并返回其值
        T& front()const{return head->data;}// —— 返回首部元素的值
        T& back()const; //—— 返回尾部元素的值
        bool insert(const size_t& index,const T& value); //—— 插入值到指定的索引，并把当前索引的元素指向到新的元素
        bool erase(const size_t& index); //—— 删除指定索引的节点
        size_t value_n_from_end(const size_t& index)const; //—— 返回倒数第 n 个节点的值
        void reverse(); //—— 逆序链表
        bool remove_value(const T& value);//—— 删除链表中指定值的第一个元素
    };
    



    
} // namespace xie



#endif