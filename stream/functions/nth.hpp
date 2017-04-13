#ifndef NTH_HPP
#define NTH_HPP

#include "../function.hpp"

#include <iostream>

class Nth : public Function, public Immediately {
  public:
  Nth(size_t arg) : arg(arg) {}
  template<typename T>
  auto apply(Stream<T>&& lhs) {
    return lhs.nth(arg);
  }
  size_t arg;
};

auto nth(size_t index){
  return Nth(index);  
}

#endif


