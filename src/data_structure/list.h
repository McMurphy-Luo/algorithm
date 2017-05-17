//
// Created by luojiayi on 5/16/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_LIST_H
#define ALGORITHM_DATA_STRUCTURE_LIST_H
#include <cstddef>

namespace algorithm{
    template <T>
    struct Node{
        T payload;
        T* next;
        T* previous;
    };

    template <T>
    class List{
    public:
        List();

    private:
        Node<T> first_;
        Node<T> last;
        size_t length_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_LIST_H
