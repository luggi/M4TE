#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

using namespace std;

template<class T>
class Stack {
    private:
        vector<T> elems;

    public:
        // push element to stack
        void push(const T &e);

        // pop element from stack
        // may throw out_of_range exception
        T pop();

        // check if stack is empty
        bool empty() const;

        // drop all elements of the stack
        void clear();
};

#endif
