#ifndef SUM_HPP
#define SUM_HPP

#include "../function.hpp"

#include <iostream>

class Sum : public Function, public Immediately {
  public:
  Sum() {}
  template<typename T>
  auto apply(const Stream<T>& lhs) {
    return lhs.sum();
  }
};

auto sum(){
  return Sum();  
}

#endif


