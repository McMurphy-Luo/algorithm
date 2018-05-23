//
// Created by luojiayi on 5/17/17.
//
#ifndef ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H
#define ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H

#include <cstddef>
#include <memory>
#include <cassert>

namespace algorithm
{
    namespace data_structure
    {
        template<typename T>
        class ArrayList {
        public:
            typedef T value_type;
            typedef std::size_t size_type;

        public:
            ArrayList() :
                size_(0),
                located_(0),
                begin_(nullptr)
            {
                // do nothing
            }

            ArrayList(const ArrayList& another)
                : ArrayList()
            {
                for (size_type index = 0; index < another.size_; ++index) {
                    add(another[index]);
                }
            }

            ArrayList &operator=(const ArrayList& rhs)
            {
                if (this == &rhs) return *this;
                clear();
                for (size_type index = 0; index < rhs.size_; ++index) {
                    add(rhs[index]);
                }
                return *this;
            }

            ~ArrayList()
            {
                clear();
            }

            size_type size() const
            {
                return size_;
            }

            value_type get(size_type index) const
            {
                return (*this)[index];
            }

            value_type& operator[](size_type index)
            {
                return *(begin_ + index);
            }

            const value_type& operator[](size_type index) const
            {
                return *(begin_ + index);
            }

            void add(const value_type& data)
            {
                if (size_ == located_) {
                    reallocate();
                }
                assert(located_ > size_);
                new(begin_ + size_) value_type(data);
                ++size_;
            }

            value_type remove(size_type index)
            {
                value_type result = *(begin_ + index);
                (begin_ + index)->~value_type();
                for (value_type *moving = begin_ + index + 1; moving < begin_ + size_; moving++) {
                    new(moving - 1) T(*moving);
                    moving->~value_type();
                }
                --size_;
                return result;
            }

            void insert(const value_type &data, size_type before)
            {
                if (size_ == located_) reallocate();
                value_type *moving = begin_ + size_ - 1;
                for (; moving >= begin_ + before; --moving) {
                    new(moving + 1) T(*(moving));
                    moving->~value_type();
                }
                new(begin_ + before) T(data);
                ++size_;
            }

            void clear()
            {
                for (size_type index = 0; index < size_; ++index) {
                    (begin_ + index)->~value_type();
                }
                free(begin_);
                located_ = size_ = 0;
                begin_ = nullptr;
            }

        protected:
            void reallocate()
            {
                if (size_ == 0) {
                    begin_ = static_cast<value_type*>(malloc(sizeof(value_type)));
                    located_ = 1;
                    return;
                }
                size_type next_located = located_ * 2;
                value_type* new_begin = static_cast<value_type*>(malloc(sizeof(value_type) * next_located));
                move(new_begin, new_begin + next_located - 1);
                located_ = next_located;
            }

            void move(value_type *new_begin, value_type *new_end)
            {
                assert(new_end > new_begin);
                assert(new_end == size_ * 2 + new_begin - 1);

                for (size_type index = 0; index < size_; ++index) {
                    new(new_begin + index) value_type(*(begin_ + index));
                    (begin_ + index)->~value_type();
                }
                free(begin_);
                begin_ = new_begin;
            }

        private:
            size_type size_;
            size_type located_;
            value_type* begin_;
        };
    }
}
#endif // ALGORITHM_DATA_STRUCTURE_ARRAY_LIST_H
