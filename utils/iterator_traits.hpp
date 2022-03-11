#ifndef TF_ITERATOR_TRAITS
#define TF_ITERATOR_TRAITS
#include <iterator>


namespace ft {

	template <typename Iterator>
	class iterator_traits {
		public:
			//types
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	class iterator_traits<T*> {
		public:
			//types
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};

	template <typename T>
	class iterator_traits<const T*> {
		public:
			//types
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};

} // ft

#endif
