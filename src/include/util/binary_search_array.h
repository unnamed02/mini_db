#include "common/config.h"
#include "util/array_header.h"
#include "util/array_block.h"

namespace mini_db{

//we assume that you can use a BinarySearchArray as a BinarySearchSearchArray's header,that is two level header
//eg : BinarySearchArray<duration_t,page_id_t> content_array(new BinarySearchArray<duration,Block*> header_array(linkd_header));
//and we provide another type of header named linked header
//when the header is too large to store in a linked header (now you must go through the link list to find a certain key)
//you should use 

template<typename KeyType,typename ValueType>
class BinarySearchArray : public ArrayHeader<KeyType,ValueType>{
    private:
    ArrayHeader<KeyType,ArrayBlock*>* _header_ptr;

    public:
    BinarySearchArray(ArrayHeader<KeyType,ArrayBlock*>* header_ptr){
        this->_header_ptr = header_ptr;
    }

    ValueType find(KeyType duration);

    bool insert(KeyType start,ValueType value);

    bool persist();

};

}