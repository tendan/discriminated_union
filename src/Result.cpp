#ifndef DISCRIMINATED_UNION_RESULT_CPP
#define DISCRIMINATED_UNION_RESULT_CPP
#endif

#include "Result.h"

template <class T, class E>
bool Result<T, E>::isOk() const {
    return mResultType == VALUE;
}

template <class T, class E>
bool Result<T, E>::isError() const {
    return mResultType == ERROR;
}

template <class T, class E>
T Result<T, E>::unwrapOr(T defaultValue) const {
    return isOk() ? mValue : defaultValue;
}

template <class T, class E>
T Result<T, E>::unwrapOrElse(std::function<T(E)> fn) const {
    return isOk() ? mValue : fn(mError);
}

template<class T, class E>
template<class U>
Result<U, E>&& Result<T, E>::map(std::function<U(T)> fn) const {
    switch (mResultType) {
        case VALUE: return std::move(Result<U, E>(fn(mValue)));
        case ERROR: return std::move(this);
    }
}

template<class T, class E>
template<class U>
U Result<T, E>::mapOr(U defaultValue, std::function<U(T)> fn) const {
    switch (mResultType) {
        case VALUE: return fn(mValue);
        case ERROR: return defaultValue;
    }
}

template<class T, class E>
template<class F>
Result<T, F> Result<T, E>::mapErr(std::function<F(E)> fn) const {

}
