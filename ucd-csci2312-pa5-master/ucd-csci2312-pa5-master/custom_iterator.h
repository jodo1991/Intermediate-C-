//
// Created by Joseph Dodson on 5/6/2016.
//

#ifndef UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
#define UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H

// Naive partial implementation of a custom iterator.
// After Jeet Sukumaran https://github.com/jeetsukumaran

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>

namespace CS2312 {

    template <typename T>
    class fixed_array {

    public:

        typedef std::size_t size_type;

        class iterator {

        public:

            typedef iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            iterator(pointer ptr):__ptr(ptr){};
            //prefix
            self_type operator++(){
                __ptr++;
                return *this;
            }
            //postfix
            self_type operator++(int junk){
                self_type temp = *this;
                __ptr++;
                return temp;
            }
            reference operator*(){return *__ptr;}
            pointer operator->(){return __ptr;}
            bool operator==(const self_type& rhs) const{return (__ptr == rhs.__ptr);}
            bool operator!=(const self_type& rhs) const{return (__ptr != rhs.__ptr);}

        private:

            pointer __ptr;

        };

        class const_iterator {

        public:

            typedef const_iterator self_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::forward_iterator_tag iterator_category;
            typedef size_type difference_type;

            const_iterator(pointer ptr):__ptr(ptr){};
            //prefix
            self_type operator++(){return ++__ptr;}
            //postfix
            self_type operator++(int junk){return __ptr++;}
            const value_type& operator*() const{return *__ptr;}
            const value_type* operator->() const{return __ptr;}
            bool operator==(const self_type& rhs) const{return (__ptr == rhs.__ptr);}
            bool operator!=(const self_type& rhs) const{return (__ptr != rhs.__ptr);}

        private:

            pointer __ptr;

        };


        fixed_array(size_type size){
            __size = size;
            __data = new T[__size];
        }

        fixed_array(std::initializer_list<T> list){
            __size = list.size();
            //allocate appropriate size array and set values from list
            __data = new T[__size];
            for(int count = 0; count < list.size(); ++count){
                __data[count] = *(list.begin()+count);
            }
        }

        ~fixed_array(){delete [] __data;}

        size_type size() const{return __size;}

        T& operator[](size_type index){return __data[index];}

        const T& operator[](size_type index) const{return __data[index];}

        iterator begin(){return iterator(__data);}

        iterator end(){return fixed_array::iterator(__data+__size);}

        const_iterator begin() const{return const_iterator(__data);}

        const_iterator end() const{return const_iterator(__data+__size);}

    private:

        T* __data;
        size_type __size;

    };

}

#endif //UCD_CSCI2312_PA5_IMPL_CUSTOM_ITERATOR_H
