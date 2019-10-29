
/* NOTE: This is an internal header file, included by other DST headers.
 *   You should not attempt to use it directly.
 */

#ifndef ___DST_INTERNAL_ITERATOR_BASE_H
#define ___DST_INTERNAL_ITERATOR_BASE_H

// This file contains all of the general iterator-related utilities.
// The internal file dst_iterator.h contains predefined iterators,
// such as front_insert_iterator and istream_iterator.

#include "concept_checks.hpp"

__DST_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// The base classes input_iterator, output_iterator, forward_iterator,
// bidirectional_iterator, and random_access_iterator are not part of
// the DST standard.  (They have been replaced by struct iterator.)
// They are included for backward compatibility with the  DST.

template <class _Tp, class _Distance>
struct input_iterator {
    typedef input_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

struct output_iterator {
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;
};

template <class _Tp, class _Distance>
struct forward_iterator {
    typedef forward_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct bidirectional_iterator {
    typedef bidirectional_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct random_access_iterator {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

#ifdef __DST_USE_NAMESPACES
template <class _Category, class _Tp, class _Distance = ptrdiff_t,
          class _Pointer = _Tp *, class _Reference = _Tp &>
struct iterator {
    typedef _Category iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Pointer pointer;
    typedef _Reference reference;
};
#endif /* __DST_USE_NAMESPACES */

#ifdef __DST_CLASS_PARTIAL_SPECIALIZATION

template <class _Iterator>
struct iterator_traits {
    typedef typename _Iterator::iterator_category iterator_category;
    typedef typename _Iterator::value_type value_type;
    typedef typename _Iterator::difference_type difference_type;
    typedef typename _Iterator::pointer pointer;
    typedef typename _Iterator::reference reference;
};

template <class _Tp>
struct iterator_traits<_Tp *> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp>
struct iterator_traits<const _Tp *> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef const _Tp *pointer;
    typedef const _Tp &reference;
};

// The overloaded functions iterator_category, distance_type, and
// value_type are not part of the DST standard.  (They have been
// replaced by struct iterator_traits.)  They are included for
// backward compatibility with the  DST.

// We introduce internal names for these functions.

template <class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
__iterator_category(const _Iter &) {
    typedef typename iterator_traits<_Iter>::iterator_category _Category;
    return _Category();
}

template <class _Iter>
inline typename iterator_traits<_Iter>::difference_type *
__distance_type(const _Iter &) {
    return static_cast<typename iterator_traits<_Iter>::difference_type *>(0);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::value_type *
__value_type(const _Iter &) {
    return static_cast<typename iterator_traits<_Iter>::value_type *>(0);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
iterator_category(const _Iter &__i) {
    return __iterator_category(__i);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::difference_type *
distance_type(const _Iter &__i) {
    return __distance_type(__i);
}

template <class _Iter>
inline typename iterator_traits<_Iter>::value_type *
value_type(const _Iter &__i) {
    return __value_type(__i);
}

#define __ITERATOR_CATEGORY(__i) __iterator_category(__i)
#define __DISTANCE_TYPE(__i) __distance_type(__i)
#define __VALUE_TYPE(__i) __value_type(__i)

#else /* __DST_CLASS_PARTIAL_SPECIALIZATION */

template <class _Tp, class _Distance>
inline input_iterator_tag
iterator_category(const input_iterator<_Tp, _Distance> &) {
    return input_iterator_tag();
}

inline output_iterator_tag iterator_category(const output_iterator &) {
    return output_iterator_tag();
}

template <class _Tp, class _Distance>
inline forward_iterator_tag
iterator_category(const forward_iterator<_Tp, _Distance> &) {
    return forward_iterator_tag();
}

template <class _Tp, class _Distance>
inline bidirectional_iterator_tag
iterator_category(const bidirectional_iterator<_Tp, _Distance> &) {
    return bidirectional_iterator_tag();
}

template <class _Tp, class _Distance>
inline random_access_iterator_tag
iterator_category(const random_access_iterator<_Tp, _Distance> &) {
    return random_access_iterator_tag();
}

template <class _Tp>
inline random_access_iterator_tag iterator_category(const _Tp *) {
    return random_access_iterator_tag();
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const input_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const forward_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const bidirectional_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const random_access_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp>
inline _Tp *value_type(const _Tp *) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *distance_type(const input_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *distance_type(const forward_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *
distance_type(const bidirectional_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *
distance_type(const random_access_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp>
inline ptrdiff_t *distance_type(const _Tp *) {
    return (ptrdiff_t *)(0);
}

// Without partial specialization we can't use iterator_traits, so
// we must keep the old iterator query functions around.

#define __ITERATOR_CATEGORY(__i) iterator_category(__i)
#define __DISTANCE_TYPE(__i) distance_type(__i)
#define __VALUE_TYPE(__i) value_type(__i)

#endif /* __DST_CLASS_PARTIAL_SPECIALIZATION */

template <class _InputIterator, class _Distance>
inline void __distance(_InputIterator _first, _InputIterator _last,
                       _Distance &__n, input_iterator_tag) {
    while (_first != _last) {
        ++_first;
        ++__n;
    }
}

template <class _RandomAccessIterator, class _Distance>
inline void __distance(_RandomAccessIterator _first,
                       _RandomAccessIterator _last, _Distance &__n,
                       random_access_iterator_tag) {
    __DST_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    __n += _last - _first;
}

template <class _InputIterator, class _Distance>
inline void distance(_InputIterator _first, _InputIterator _last,
                     _Distance &__n) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __distance(_first, _last, __n, iterator_category(_first));
}

#ifdef __DST_CLASS_PARTIAL_SPECIALIZATION

template <class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(_InputIterator _first, _InputIterator _last, input_iterator_tag) {
    typename iterator_traits<_InputIterator>::difference_type __n = 0;
    while (_first != _last) {
        ++_first;
        ++__n;
    }
    return __n;
}

template <class _RandomAccessIterator>
inline typename iterator_traits<_RandomAccessIterator>::difference_type
__distance(_RandomAccessIterator _first, _RandomAccessIterator _last,
           random_access_iterator_tag) {
    __DST_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    return _last - _first;
}

template <class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
distance(_InputIterator _first, _InputIterator _last) {
    typedef
        typename iterator_traits<_InputIterator>::iterator_category _Category;
    __DST_REQUIRES(_InputIterator, _InputIterator);
    return __distance(_first, _last, _Category());
}

#endif /* __DST_CLASS_PARTIAL_SPECIALIZATION */

template <class _InputIter, class _Distance>
inline void __advance(_InputIter &__i, _Distance __n, input_iterator_tag) {
    while (__n--)
        ++__i;
}

#if defined(__llvm) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1183
#endif

template <class _BidirectionalIterator, class _Distance>
inline void __advance(_BidirectionalIterator &__i, _Distance __n,
                      bidirectional_iterator_tag) {
    __DST_REQUIRES(_BidirectionalIterator, _BidirectionalIterator);
    if (__n >= 0)
        while (__n--)
            ++__i;
    else
        while (__n++)
            --__i;
}

#if defined(__llvm) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1183
#endif

template <class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n,
                      random_access_iterator_tag) {
    __DST_REQUIRES(_RandomAccessIterator, _RandomAccessIterator);
    __i += __n;
}

template <class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __advance(__i, __n, iterator_category(__i));
}

__DST_END_NAMESPACE

#endif /* ___DST_INTERNAL_ITERATOR_BASE_H */
