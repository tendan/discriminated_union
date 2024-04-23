#ifndef DISCRIMINATED_UNION_RESULT_CPP
#define DISCRIMINATED_UNION_RESULT_CPP
#endif

#include "Result.h"

template <class T, class E>
inline T Result<T, E>::getValue() const {
    return std::get<T>(mResultField);
}

template <class T, class E>
inline E Result<T, E>::getError() const {
    return std::get<E>(mResultField);
}

template <class T, class E>
inline bool Result<T, E>::isOk() const {
    return mResultType == VALUE;
}

template <class T, class E>
inline bool Result<T, E>::isError() const {
    return mResultType == ERROR;
}

template <class T, class E>
T Result<T, E>::unwrapOr(T defaultValue) const {
    return isOk() ? getValue() : defaultValue;
}

template <class T, class E>
T Result<T, E>::unwrapOrElse(std::function<T(E)> fn) const {
    return isOk() ? getValue() : fn(getError());
}

template<class T, class E>
template<class U>
Result<U, E> Result<T, E>::map(std::function<U(T)> fn) const {
    switch (mResultType) {
        case VALUE: return Result<U, E>(fn(getValue()));
        default: return *this; // Compile warning evade
    }
}

template<class T, class E>
template<class U>
U Result<T, E>::mapOr(U defaultValue, std::function<U(T)> fn) const {
    switch (mResultType) {
        case VALUE: return fn(getValue());
        default: return defaultValue; // Compile warning evade
    }
}

template<class T, class E>
template<class F>
Result<T, F> Result<T, E>::mapErr(std::function<F(E)> fn) const {
    switch (mResultType) {
        case VALUE: return *this;
        default: return Result<T, F>(fn(getError())); // Compile warning evade
    }
}

template<class T, class E>
template<class U>
U Result<T, E>::mapOrElse(std::function<U(E)> defaultFn, std::function<U(T)> valueFn) const {
    switch (mResultType) {
        case VALUE: return valueFn(getValue());
        default: return defaultFn(getError()); // Compile warning evade
    }
}

template<class T, class E>
bool Result<T, E>::operator==(Result<T, E> other) const {
    switch (mResultType) {
        case VALUE: return getValue() == other.getValue();
        default: return getError() == other.getError(); // Compile warning evade
    }
}