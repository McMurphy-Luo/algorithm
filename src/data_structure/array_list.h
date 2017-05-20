//
// Created by luojiayi on 5/17/17.
//
#ifndef ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H
#define ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H
#include <cstddef>
#include <memory>

namespace algorithm{
    template <typename T>
    class ArrayList{
    public:
        ArrayList():
                size_(0),
                located_(0),
                begin_(nullptr),
                end_(nullptr)
        {

        }
        size_t length() const {
            return size_;
        }
        void push(T data){

        }
        T pop(){

        }
    private:
        void reallocate(){
            if (size_ == 0){
                size_ = 1;
                end_ = begin_ = operator new(sizeof T) ;
                return;
            }
            size_t next_size = size_ * 2;
            next_size = next_size > size_ ? next_size : next_size + 1;

            T* current = begin_;
            T* new_begin = new T[next_size];
            while(current != end_){

            }


            T* new_current;
            T* new_end;



        }

    private:
        std::size_t size_;
        std::size_t located_;
        T* begin_;
        T* current_;
        T* end_;
    };
}
#endif // ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H