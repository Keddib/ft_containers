#ifndef FT_ALLOCATOR_HPP
#define FT_ALLOCATOR_HPP

#include <cstdlib>

namespace ft{

	template<typename T>
	class Simple_alloc
	{
		// use std::malloc() and std::free() to allocate and deallocate bytes
		public:
			//types
			typedef size_t				size_type;
			typedef ptrdiff_t			difference_type;
			typedef T*					pointer;
			typedef const T*			const_pointer;
			typedef T&					reference;
			typedef const T&			const_reference;
			typedef T					value_type;

			// member func
			Simple_alloc() {}

			T* allocate(size_t n) { return (T *)std::malloc( n * sizeof(T) ); }

			void construct (T* p, const T val = T()) { p = new((void *)p) T(val); }

			void destroy(T *p) { ((T*)p)->~T(); }

			void deallocate(T* p, size_t n) { std::free(p); }

			size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }
	};
} // ft

#endif
