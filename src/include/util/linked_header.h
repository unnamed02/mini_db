#pragma once
namespace mini_db{

template<typename KeyType,typename ValueType>
class LinkedHeader : public ArrayHeader<KeyType,ValueType>{
    private:
    KeyType _start;
    KeyType _end;

    LinkedHeader* _next;
    
    public:
    LinkedHeader(){

    };

    ValueType find(KeyType key);

    bool insert(KeyType key,ValueType value);

    bool persist();

};
}