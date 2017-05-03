//
// Created by Joseph on 5/2/2016.
//

#ifndef UCD_CSCI2312_PA5_IMPL_LESS_FUNCTOR_H
#define UCD_CSCI2312_PA5_IMPL_LESS_FUNCTOR_H

#include <cstring>

namespace CS2312{

    template <typename T>
    class less {
    public:
        bool operator() (const T &lhs, const T &rhs) {
            return (lhs < rhs);
        }
    };

    template <>
    class less<std::string> {
    public:
        bool operator() (const std::string &lhs, const std::string &rhs){
            return (lhs < rhs);
        }
    };


    template <>
    class less<const char*> {
    public:
        bool operator() (const char *lhs, const char *rhs){
            return (strcmp(lhs, rhs) < 0);
        }
    };
}

#endif //UCD_CSCI2312_PA5_IMPL_LESS_FUNCTOR_H
