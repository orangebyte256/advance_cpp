#ifndef REDUCE_HPP
#define REDUCE_HPP

#include "../function.hpp"

#include <iostream>

template<typename Identity, typename Accumulator>
class Reduce : public Function, public Immediately {
  public:
  Reduce(Identity&& identityFn, Accumulator&& accum) : arg1(std::forward<Identity>(identityFn)), arg2(std::forward<Accumulator>(accum)) {}
  template<typename T>
  auto apply(const Stream<T>& lhs) {
    return lhs.reduce(std::forward<Identity>(arg1), std::forward<Accumulator>(arg2));
  }
  Identity &&arg1;
  Accumulator &&arg2;
};

#include <tuple>


template <typename T>
struct function_traits
    : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'


template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};


template<typename T>
auto reduce(T &&my_arg){
     typedef function_traits<T> traits;
		 typedef typename traits::result_type res;
     auto f = [](res v){return v;};
     return Reduce<decltype(f),T>(std::move(f),std::forward<T>(my_arg));  
}

template<typename T, typename K>
auto reduce(T &&arg1, K &&arg2){
  return Reduce<T,K>(std::forward<T>(arg1),std::forward<K>(arg2));  
}



#endif


