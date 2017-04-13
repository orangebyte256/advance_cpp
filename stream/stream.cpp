#include "stream.hpp"
#include "A.hpp"
#include <initializer_list>
#include <iostream>

int main() {
//    template_fn(5);
//    auto s = MakeStream(std::vector<int>({1,2,3}));
//    std::vector<A> vec{A()};

//      std::vector<A> vec;
//      vec.push_back(A());
//      A a = vec[0];
//      auto t = A();
//        std::vector<int> res{1,2,3,4,5};
//        auto s = MakeStream(res);

      auto s = MakeStream(A());
//      A a = l[0];  
      
      auto l = s | map([](auto &&a){std::cout << "1"; return std::move(a);}); //| to_vector(); //| print_to(std::cout);
      auto z = l | [](auto &&a){return std::move(a);};
      auto y = z | to_vector();

//			int l = s | reduce([](int a,int b){return a+b;});// | print_to(std::cout);
//		std::cout << (s | to_vector()).size();
//      auto s = MakeStream(1,2,3,4,5);
//			auto b = s;
//    auto s = MakeStream(vec.begin(), vec.end());
//    auto s = MakeStream([](int k) {return k * 2;}, 2);
//  static_assert(false);
//  s |  print_to(std::cout);
//      test([](int a){return a;});

//		auto z = s | map([](int a){return std::to_string(a) + "1";}); //| skip(1) | print_to(std::cout);
//			std::cout << (z | nth(2));
//			std::cout << ((s | group(2) | to_vector()).size());
//		std::cout << (s | sum());
//  (s | ([](int a){return a * 2;}) | filter([](int a){return a>2;}) | filter([](int a){return a>2;}) | print_to(std::cout) << "aaa") << std::endl; 
	
//  std::cout << a;
  return 0;
};
