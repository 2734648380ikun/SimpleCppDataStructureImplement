#ifndef _Array_XIE
#define _Array_XIE
#include<memory>
namespace xie
{
    constexpr size_t _MIN_CAPACITIES=16;
    constexpr size_t _MAX_CAPACITIES=1000000;
    template<class T>
    class array
    {
    using  arr_ptr= std::unique_ptr<T[]>;
    private:
        arr_ptr arr;
        size_t size_arr;
        size_t capacities_arr;
        void Resize(size_t size_new){
            increse(size_new);
            decrese(size_new);
            size_arr=size_new;
        }
        void increse(size_t size_new){
            if(size_new>=capacities_arr&&size_new<_MAX_CAPACITIES){
                arr_ptr t=std::move(arr);
                arr=arr_ptr(new T[2*capacities_arr]());
                capacities_arr*=2;
                for(size_t i=0;i<size_arr;++i){
                    arr[i]=t[i];
                }
            }
        }
        void decrese(size_t size_new){
            if(size_new<=capacities_arr/4.f){
                arr_ptr t=std::move(arr);
                capacities_arr/=2;
                arr=arr_ptr(new T[capacities_arr/2]());
                for(size_t i=0;i<size_arr;++i){
                    arr[i]=t[i];
                }
            }
        }
    public:
        array():arr(nullptr),size_arr(0),capacities_arr(_MIN_CAPACITIES){
            arr=arr_ptr(new T[capacities_arr]());
        }
        array(const array& other);
        array(const T& value,const size_t& num=_MIN_CAPACITIES);
        array& operator=(const array& other);
        array(array&& other):arr(std::move(other.arr)),size_arr(other.size_arr),
                                        capacities_arr(other.capacities_arr){}
        array& operator=(array&& other){
            arr=nullptr;
            capacities_arr=std::move(other.capacities_arr);
            size_arr=std::move(other.size_arr);
            arr=std::move(other.arr);
            return *this;
            }
        T& operator[](long long index)const{return at(index);};
        ~array()=default;
        size_t size()const{return size_arr;}
        size_t capacity()const{return capacities_arr;}
        bool is_empty()const{return size_arr==0;}
        T& at(const long long&index)const{if(index>=size_arr||index<0) throw "数组索引越界";else return arr[index];}
        void push(const T& value);
        bool insert(const long long& index,const T& value);
        void prepend(const T& value);
        void delete_at(const long long& index);
        array<size_t> remove(const T& value);
        long long find(const T& value)const;
        void resize(const size_t& size){Resize(size);}
    };

} // namespace xie




#endif