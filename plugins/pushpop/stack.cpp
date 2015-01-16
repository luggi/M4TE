#include "stack.h"

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
