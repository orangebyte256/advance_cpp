#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../function.hpp"

#include <iostream>

class To_vector : public Function, public Immediately {
  public:
  To_vector() {}
  template<typename T>
  auto apply(T&& lhs) {
    return lhs.to_vector();
  }
};

auto &&to_vector(){
  return std::move(To_vector());  
}

#endif


