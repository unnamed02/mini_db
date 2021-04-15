#include "common/config.h"
#include "util/array_block.h"

namespace mini_db{

template<typename key_type,typename value_type>
class ArrayHeader{

    public:

    virtual value_type find(key_type key) = 0;

    virtual bool insert(key_type key,value_type value);

    virtual bool persist();

};

}