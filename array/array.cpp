#include"array.h"
namespace xie
{
    template<class T>
    array<T>::array(const array& other){
        capacities_arr=other.capacities_arr;
        size_arr=other.size_arr;
        arr=arr_ptr(new T[capacities_arr]);
        for(size_t i=0;i<other.size_arr;++i){
            arr[i]=other[i];
        }
    }
    template<class T>
    array<T>::array(const T& value,const size_t& num){
        capacities_arr=num;
        size_arr=num;
        arr=arr_ptr(new T[capacities_arr]{value});
        
    }
    template<class T>
    array<T>& array<T>::operator=(const array& other){
        if(other==*this){
            return *this;
        }
        capacities_arr=other.capacities_arr;
        size_arr=other.size_arr;
        arr=arr_ptr(new T[other.capacities_arr]);
        for(size_t i=0;i<other.size_arr;++i){
            arr[i]=other[i];
        }
        return *this;
    }
    template<class T>
    inline void array<T>::push(const T& value){
        increse(size_arr);
        arr[size_arr]=value;
        ++size_arr;
    }
    template<class T>
    inline bool array<T>::insert(const long long& index,const T& value){
        increse(size_arr);
        ++size_arr;
        if(index<0||index>size_arr-1) return false;
        for(int i=size_arr;i>index;--i){
            arr[i]=arr[i-1];
        }
        arr[index]=value;
        return true;
    }
    template<class T>
    inline void array<T>::prepend(const T& value){
        insert(0,value);
    }
    template<class T>
    inline void array<T>::delete_at(const long long& index){
        decrese(size_arr);
        at(index);
        for(size_t i=index;i<size_arr;++i){
            arr[i]=arr[i+1];
        }
        --size_arr;
    }
    template<class T>
    inline array<size_t> array<T>::remove(const T& value){
        array<size_t> t=array<size_t>();
        array<size_t>t1=array<size_t>();
        for(size_t i=0;i<size_arr;++i){
            if(arr[i]!=value){
                t.push(arr[i]);
            }else{
                t1.push(i);
            }
        }
        for(size_t i=0;i<t.size();++i){
            arr[i]=t[i];
        }
        size_arr=t.size();
        decrese(size_arr);
        return t1;
    }
    template<class T>
    inline long long  array<T>::find(const T& value)const{
        for(size_t i=0;i<size_arr;++i){
            if(arr[i]==value){
                return i;
            }
        }
        return -1;
    }
} // namespace xie
