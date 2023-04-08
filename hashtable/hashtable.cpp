#include"hashtable.h"
#include<iostream>
namespace xie
{
    template<class T_key,class T_value>
    size_t hashtable<T_key,T_value>::FindPos(const T_key& key)const{
        size_t currentPos=hash(key);
        while(_hashtable[currentPos].info!=EMPTY&&_hashtable[currentPos].key!=key){
            size_t offset=1;
            currentPos+=offset;
            currentPos%=_hashtable.size();
        }
        return currentPos;
    }
    template<class T_key,class T_value>
    void hashtable<T_key,T_value>::add(const T_key& key,const T_value& value){
        size_t pos=FindPos(key);
        _hashtable[pos].info=ACTIVE;
        _hashtable[pos].key=key;
        _hashtable[pos].value=value;
        ++size_table;
        rehash();
    }
    template<class T_key,class T_value>
    bool hashtable<T_key,T_value>::exists(const T_key& key)const{
        size_t pos=FindPos(key);
        object t=_hashtable.at(pos);
        return t.info==ACTIVE;
    }
    template<class T_key,class T_value>
    inline T_value& hashtable<T_key,T_value>::get(const T_key& key)const{
        size_t pos=FindPos(key);
        return _hashtable[pos].value;
    }
    template<class T_key,class T_value>
    bool hashtable<T_key,T_value>::remove(const T_key& key){
        if(!exists(key)) return false;
        size_t pos=FindPos(key);
        _hashtable.at(pos).info=DELETED;
        --size_table;
        return true;
    }
    template<class T_key,class T_value>
    void hashtable<T_key,T_value>::rehash(){
        if(2*size_table>=capacity()){
            array<object> t=_hashtable;
            _hashtable=array<object>(object(),capacity()*2);
            _hashtable.resize(capacity());
            size_table=0;
            for(size_t i=0;i<t.size();++i){
                if(t[i].info==ACTIVE){
                    add(t[i].key,t[i].value);
                }
            }
        }
        
    }
} // namespace xie