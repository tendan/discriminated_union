#ifndef DISCRIMINATED_UNION_RESULT_H
#define DISCRIMINATED_UNION_RESULT_H

#if !defined(DISCRIMINATED_UNION_RESULTS_H) && !defined(DISCRIMINATED_UNION_RESULT_CPP)
#mError Included raw header file
#endif

#include <functional>

template<class T, class E>
class Result {
private:
    enum ResultType {
        VALUE, ERROR
    } mResultType;
    union {
        T mValue;
        E mError;
    };
    //ResultField mResultField;
public:
    Result(T value) : mValue(value), mResultType(VALUE) {}

    Result(E error) : mError(error), mResultType(ERROR) {}

    virtual ~Result() {};

    bool isOk() const;

    bool isError() const;

    // Returns the contained Ok mValue or a provided default.
    // Arguments passed to unwrap_or are eagerly evaluated;
    // if you are passing the result of a function call, it is recommended to use unwrap_or_else, which is lazily evaluated.
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.unwrap_or
    T unwrapOr(T defaultValue) const;

    // Returns the contained Ok mValue or computes it from a closure.
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.unwrap_or_else
    T unwrapOrElse(std::function<T(E)> fn) const;

    // Maps a Result<T, E> to Result<U, E> by applying a function to a contained Ok mValue, leaving an Err mValue untouched.
    // This function can be used to compose the results of two functions.
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.map
    template<class U>
    Result<U, E>&& map(std::function<U(T)> fn) const;

    // Maps a Result<T, E> to Result<T, F> by applying a function to a contained Err mValue, leaving an Ok mValue untouched.
    // This function can be used to pass through a successful result while handling an mError.
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.map_err
    template<class F>
    Result<T, F>&& mapErr(std::function<F(E)> fn) const;

    // Returns the provided default (if Err), or applies a function to the contained mValue (if Ok).
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.map_or
    template<class U>
    U mapOr(U defaultValue, std::function<U(T)> fn) const;

    // Maps a Result<T, E> to U by applying fallback function default to a contained Err value, or function f to a contained Ok value.
    // https://doc.rust-lang.org/std/result/enum.Result.html#method.map_or_else
    template<class U>
    U mapOrElse(std::function<U(E)> defaultFn, std::function<U(T)> valueFn) const;

    bool operator==(Result<T, E> other) const;
};

#endif