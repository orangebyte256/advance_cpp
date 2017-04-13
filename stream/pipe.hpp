#include "function.hpp"
#include "functions/print_to.hpp"

Print_to &&operator<<(Print_to &&p,const std::string &t)
{
		p.add(t);
    return std::move(p);
}


template<typename T, typename F,
typename K = typename std::enable_if<!std::is_base_of<Function, F>::value,F>::type>
auto operator|(T&& lhs, F&& rhs){
  return [&](){return lhs().map(rhs);};
}


template<typename T, typename F,
typename U = decltype(std::declval<F>().apply(std::declval<T>()())),
typename K = typename std::enable_if<std::is_base_of<Immediately, F>::value,F>::type,
typename Z = typename std::enable_if<std::is_base_of<Function, F>::value,F>::type>
U operator|(T&& lhs, F &&rhs){
 	return rhs.apply(lhs());
}


template<typename T, typename F,
typename U = decltype(std::declval<T>()()),
typename Z = typename std::enable_if<std::is_base_of<Function, F>::value,F>::type,
typename K = typename std::enable_if<!std::is_base_of<Immediately, F>::value,F>::type>
auto operator|(T &&lhs, F &&rhs){
  return [&](){return rhs.apply(lhs());};
}

