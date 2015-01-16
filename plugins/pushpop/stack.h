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

template<class T>
void Stack<T>::push(const T &e)
{
    elems.push_back(e);
}

template<class T>
T Stack<T>::pop()
{
    if (elems.empty()) {
        throw out_of_range("stack empty");
    }

    T ret = elems.back();
    elems.pop_back();
    return ret;
}

template<class T>
bool Stack<T>::empty() const
{
    return elems.empty();
}

template<class T>
void Stack<T>::clear()
{
    elems.clear();
}

#endif
