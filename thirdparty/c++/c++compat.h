#ifndef CPPCOMPAT_H
#define CPPCOMPAT_H

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
# define CPP17
#endif
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L)
# define CPP14
#endif
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus >= 201103L)
# define CPP11
#endif

/*
 * Emulate std::to_string on Android.
 *
 * Notice: there might be different solutions per
 * http://stackoverflow.com/questions/26095886/error-to-string-is-not-a-member-of-std
 */
#ifdef ANDROID

#include <string>
#include <sstream>

namespace std {
	template< typename T >
	string to_string(const T & value) {
		ostringstream ss;
		ss << value;
		return ss.str();
	}
}
#endif /* ANDROID */

#if ((defined(_MSVC_LANG) && _MSVC_LANG < 201402L) || __cplusplus < 201402L)

#include <cstddef>
#include <type_traits>
#include <memory>
#include <utility>
#include <iterator>

#ifndef CPP11
namespace std
{
	template< bool B, class T = void > struct enable_if {};
	template< class T > struct enable_if< true, T > { typedef T type; };
}
#else
namespace std
{
	template< bool B, class T = void >
	using enable_if_t         = typename std::enable_if< B, T >::type;
}
#endif

namespace std {
    template<class T> struct _Unique_if {
        typedef std::unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef std::unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename std::remove_extent<T>::type U;
            return std::unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;

    template<class Iterator>
        reverse_iterator<Iterator> make_reverse_iterator(Iterator i)
        {
            return reverse_iterator<Iterator>(i);
        }
}
#endif // !c++14

#endif // CPPCOMPAT_H
