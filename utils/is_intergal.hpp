#include <type_traits>

template <class T>
struct is_integral : public integral_constant<bool, __is_integral(T)> {};
