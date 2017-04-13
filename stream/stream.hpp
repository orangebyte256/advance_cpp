#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <future>

#include "A.hpp"

#include "function.hpp"
#include "functions/filter.hpp"
#include "functions/sum.hpp"
#include "functions/map.hpp"
#include "functions/reduce.hpp"
#include "functions/print_to.hpp"
#include "functions/to_vector.hpp"
#include "functions/skip.hpp"
#include "functions/group.hpp"
#include "functions/nth.hpp"
#include "pipe.hpp"

template<typename T>
class Stream {
public:
	typedef T type;
  
	Stream(){}
  Stream(const std::vector<T> &val) : elements(val) {};
  Stream(std::vector<T> &&val) : elements(std::move(val)) {};
  Stream(const Stream &str) : elements(str.elements){}
  Stream(Stream &&str) : elements(std::move(str.elements)){}
  Stream &operator=(const Stream &str) {elements = str.elements; return *this;}
  Stream &operator=(Stream &&str) {elements = std::move(str.elements); return *this;}

  Stream<T> &&operator()(){
		return std::move(*this);
	}

  template<typename Predicate>
  auto filter(Predicate &&predicate) {
    std::vector<T> res;
    for(auto &val : elements){
      if(predicate(val)){
        res.push_back(std::move(val));
      }
    }
    return Stream<type>(std::move(res));
  }

  template<typename Ident, typename Accum>
  auto reduce(Ident &&ident, Accum &&accum) const {
    T result = ident(elements[0]);
    for(size_t i = 1; i < elements.size(); i++){
        result = accum(result, elements[i]);
    }
    return result;
  }
  template<typename Map>
  auto map(Map &&map){
		typedef decltype(std::declval<Map>()(std::declval<T>())) type;
    std::vector<type> res;
    for(auto &val : elements){
      res.push_back(map(val));
    }
    return Stream<type>(std::move(res));
  }
   
  std::ostream& print_to(std::ostream& os, const char* delimiter, std::string text) const {
    for(auto &val : elements){
      os << val << delimiter;
    }
		os << text;
    return os;
  }

	Stream<std::vector<T>> group(const size_t n) {
		std::vector<std::vector<T>> res(ceil(double(elements.size()) / n));
		int i = 0;
		for(auto &t : elements){
			if(i % n == 0)
				res[i / n] = std::vector<T>(n);
			res[i / n][i % n] = std::move(t);
      i++;
		}
		return Stream<std::vector<T>>(std::move(res));
	}

	auto sum() const{
		T res = T();
		for(auto &t : elements){
			res+= t;
		}
		return res;
	}

	auto skip (size_t amount){
		std::vector<T> res;
		for(int i = amount; i < elements.size(); i++){
			res.push_back(std::move(elements[i]));
		}
		return Stream<T>(std::move(res));
	}

  auto &&to_vector() {
		return std::move(elements);
	}

	T& nth(size_t index){
    return elements[index];
	}

private:
  std::vector<T> elements;
};


template<typename T>
  Stream<T> MakeStream(std::initializer_list<T> lis) {
    std::vector<T> res(lis);
    return Stream<T>(res);
};


template<typename T,
  typename E = typename std::decay<decltype(*(std::declval<T>()))>::type>
Stream<E> MakeStream(T cur, T end) {
  std::vector<E> res;
  while(cur != end)
    res.push_back(*cur++);
  return Stream<E>(res);
};


template<typename E, typename T = typename std::remove_reference<E>::type::value_type>
Stream<T> MakeStream(E &&container){
  std::vector<T> res;
  for(auto &val : container){
    res.push_back(std::move(val));
  }
  return Stream<T>(std::move(res));
}


template<typename T, typename E>
void convertToVec(std::vector<T> &arr, E&& val){
  arr.push_back(std::forward<E>(val));
}

template<typename T, typename E, typename ...Args>
void convertToVec(std::vector<T> &arr, E&& val, Args&& ...args){
  arr.push_back(std::forward<E>(val));
  convertToVec(arr, std::forward<Args>(args)...);
}

Stream<char> MakeStream(){
  Stream<char> res;
  return res;
}

template<typename T, typename E = typename std::remove_reference<T>::type, typename ...Args>
Stream<E> MakeStream(T &&val, Args&& ...args){
  std::vector<E> res;
  convertToVec(res, std::forward<T>(val), std::forward<Args>(args)...);
  return Stream<E>(std::move(res));
}



template< typename T, typename U = decltype(std::declval<T>()(std::declval<int>()))>
Stream<U> MakeStream(T &&generator, int num){
  std::vector<U> res;
  for(int i = 0; i < num; i++)
    res.push_back(generator(i));
  return res;
}


