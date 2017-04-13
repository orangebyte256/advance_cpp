#ifndef A_CLASS
#define A_CLASS

struct A{
  A(){
    std::cout << "A ctor\n";
  }
  
  A(const A& other){
    std::cout << "A copy\n";
  }

  A(A&& other){
    std::cout << "A move\n";
  }

  ~A(){
    std::cout << "A d tor\n";
  }
};

#endif

