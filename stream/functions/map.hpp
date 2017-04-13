#ifndef MAP_HPP
#define MAP_HPP

#include "../function.hpp"

#include <iostream>

template<typename Func>
class Map : public Function {
  public:
  Map(Func &&arg) : arg(std::forward<Func>(arg)) {}
  template<typename T>
  auto apply(T&& lhs) {
    return lhs.map(std::forward<Func>(arg));
  }
  Func &&arg;
};

template<typename T>
auto map(T &&arg){
  return Map<T>(std::forward<T>(arg));  
}

#endif


