#ifndef FILTER_HPP
#define FILTER_HPP

#include "../function.hpp"

#include <iostream>

template<typename Predicate>
class Filter : public Function {
  public:
  Filter(Predicate &&arg) : arg(std::forward<Predicate>(arg)) {}
  template<typename T>
  auto apply(Stream<T>&& lhs) {
    return lhs.filter(std::forward<Predicate>(arg));
  }
  Predicate &&arg;
};

template<typename T>
Filter<T> filter(T &&arg){
  return Filter<T>(std::forward<T>(arg));  
}

#endif


