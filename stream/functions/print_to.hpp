#ifndef PRINT_TO_HPP
#define PRINT_TO_HPP

#include "../function.hpp"

#include <iostream>
#include <string>

class Print_to : public Function, public Immediately{
  public:
  Print_to(std::ostream& os, const char* delimiter) : 
    os_(os), delimiter_(delimiter) {}
  template<typename T>
  std::ostream& apply(const Stream<T>& lhs) {
    return lhs.print_to(os_, delimiter_, text);
  }
	void add(const std::string & val){
		text = text += val;
	}
  std::ostream& os_;
  const char* delimiter_;
	std::string text;
};

Print_to print_to(std::ostream& os, const char* delimiter = " "){
  return Print_to(os, delimiter);  
}

#endif


