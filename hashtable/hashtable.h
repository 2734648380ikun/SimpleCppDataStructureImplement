#ifndef _HASHTABLE_XIE
#define _HASHTABLE_XIE
#include<memory>
#include"../array/array.h"
#include"../array/array.cpp"
namespace xie
{
    constexpr size_t _MIN_HASHTABLE=7;
    template<class T_key,class T_value>
    class hashtable
    {
    private:
        enum EntryType{ ACTIVE,DELETED,EMPTY};
        struct object
        {
            T_value value;
            T_key key;
            EntryType info;
            object():info(EMPTY){}
            object(const object& ob):value(ob.value),key(ob.key),info(ob.info){}
            object& operator=(const object& ob){
                value=ob.value;
                key=ob.key;
                info=ob.info;
                return *this;
            }
        };
        array<object> _hashtable;
        size_t size_table;
        size_t FindPos(const T_key& key)const;
        void rehash();
    public:
        hashtable():_hashtable(array<object>()),size_table(0){_hashtable.resize(_MIN_HASHTABLE);}
        hashtable(const hashtable<T_key,T_value>& hb):_hashtable(array<object>(hb._hashtable)),size_table(hb.size_table){}
        ~hashtable()=default;
        size_t hash(const T_key& key)const{return key%capacity();}
        size_t capacity()const{return _hashtable.size();}
        size_t size()const{return size_table;}
        void add(const T_key& key,const T_value& value);
        bool exists(const T_key& key)const;
        T_value& get(const T_key& key)const;
        bool remove(const T_key& key);
    };
    

} // namespace xie

#endif