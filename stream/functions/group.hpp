#ifndef GROUP_HPP
#define GROUP_HPP

#include "../function.hpp"

#include <iostream>

class Group : public Function {
  public:
  Group(const size_t arg) : arg_(arg) {}
  template<typename T>
  auto apply(Stream<T>&& lhs) {
    return lhs.group(arg_);
  }
  const size_t arg_;
};

auto group(const size_t arg){
  return Group(arg);  
}

#endif


