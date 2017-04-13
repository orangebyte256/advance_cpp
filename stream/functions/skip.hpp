#ifndef SKIP_HPP
#define SKIP_HPP

#include "../function.hpp"

#include <iostream>

class Skip : public Function {
  public:
  Skip(size_t arg) : arg(arg) {}
  template<typename T>
  auto apply(const Stream<T>& lhs) {
    return lhs.skip(arg);
  }
  size_t arg;
};

auto skip(size_t amount){
  return Skip(amount);  
}

#endif


