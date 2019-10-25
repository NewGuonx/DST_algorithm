#ifndef ___DST_INTERNAL_NUMERIC_H
#define ___DST_INTERNAL_NUMERIC_H

__DST_BEGIN_NAMESPACE

template <class _InputIterator, class _Tp>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    for (; __first != __last; ++__first) __init = __init + *__first;
    return __init;
}

template <class _InputIterator, class _Tp, class _BinaryOperation>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init,
               _BinaryOperation __binary_op) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    for (; __first != __last; ++__first) __init = __binary_op(__init, *__first);
    return __init;
}

template <class _InputIterator1, class _InputIterator2, class _Tp>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init) {
    __DST_REQUIRES(_InputIterator2, _InputIterator);
    __DST_REQUIRES(_InputIterator2, _InputIterator);
    for (; __first1 != __last1; ++__first1, ++__first2)
        __init = __init + (*__first1 * *__first2);
    return __init;
}

template <class _InputIterator1, class _InputIterator2, class _Tp,
          class _BinaryOperation1, class _BinaryOperation2>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init,
                  _BinaryOperation1 __binary_op1,
                  _BinaryOperation2 __binary_op2) {
    __DST_REQUIRES(_InputIterator2, _InputIterator);
    __DST_REQUIRES(_InputIterator2, _InputIterator);
    for (; __first1 != __last1; ++__first1, ++__first2)
        __init = __binary_op1(__init, __binary_op2(*__first1, *__first2));
    return __init;
}

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator __partial_sum(_InputIterator __first, _InputIterator __last,
                              _OutputIterator __result, _Tp *) {
    _Tp __value = *__first;
    while (++__first != __last) {
        __value = __value + *__first;
        *++__result = __value;
    }
    return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator partial_sum(_InputIterator __first, _InputIterator __last,
                            _OutputIterator __result) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __DST_REQUIRES(_OutputIterator, _OutputIterator);
    if (__first == __last)
        return __result;
    *__result = *__first;
    return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first));
}

template <class _InputIterator, class _OutputIterator, class _Tp,
          class _BinaryOperation>
_OutputIterator __partial_sum(_InputIterator __first, _InputIterator __last,
                              _OutputIterator __result, _Tp *,
                              _BinaryOperation __binary_op) {
    _Tp __value = *__first;
    while (++__first != __last) {
        __value = __binary_op(__value, *__first);
        *++__result = __value;
    }
    return ++__result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator partial_sum(_InputIterator __first, _InputIterator __last,
                            _OutputIterator __result,
                            _BinaryOperation __binary_op) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __DST_REQUIRES(_OutputIterator, _OutputIterator);
    if (__first == __last)
        return __result;
    *__result = *__first;
    return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first),
                         __binary_op);
}

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator __adjacent_difference(_InputIterator __first,
                                      _InputIterator __last,
                                      _OutputIterator __result, _Tp *) {
    _Tp __value = *__first;
    while (++__first != __last) {
        _Tp __tmp = *__first;
        *++__result = __tmp - __value;
        __value = __tmp;
    }
    return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator adjacent_difference(_InputIterator __first,
                                    _InputIterator __last,
                                    _OutputIterator __result) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __DST_REQUIRES(_OutputIterator, _OutputIterator);
    if (__first == __last)
        return __result;
    *__result = *__first;
    return __adjacent_difference(__first, __last, __result,
                                 __VALUE_TYPE(__first));
}

template <class _InputIterator, class _OutputIterator, class _Tp,
          class _BinaryOperation>
_OutputIterator __adjacent_difference(_InputIterator __first,
                                      _InputIterator __last,
                                      _OutputIterator __result, _Tp *,
                                      _BinaryOperation __binary_op) {
    _Tp __value = *__first;
    while (++__first != __last) {
        _Tp __tmp = *__first;
        *++__result = __binary_op(__tmp, __value);
        __value = __tmp;
    }
    return ++__result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator
adjacent_difference(_InputIterator __first, _InputIterator __last,
                    _OutputIterator __result, _BinaryOperation __binary_op) {
    __DST_REQUIRES(_InputIterator, _InputIterator);
    __DST_REQUIRES(_OutputIterator, _OutputIterator);
    if (__first == __last)
        return __result;
    *__result = *__first;
    return __adjacent_difference(__first, __last, __result,
                                 __VALUE_TYPE(__first), __binary_op);
}

// Returns __x ** __n, where __n >= 0.  _Note that "multiplication"
// is required to be associative, but not necessarily commutative.

template <class _Tp, class _Integer, class _MonoidOperation>
_Tp __power(_Tp __x, _Integer __n, _MonoidOperation __opr) {
    if (__n == 0)
        return identity_element(__opr);
    else {
        while ((__n & 1) == 0) {
            __n >>= 1;
            __x = __opr(__x, __x);
        }

        _Tp __result = __x;
        __n >>= 1;
        while (__n != 0) {
            __x = __opr(__x, __x);
            if ((__n & 1) != 0)
                __result = __opr(__result, __x);
            __n >>= 1;
        }
        return __result;
    }
}

template <class _Tp, class _Integer> inline _Tp __power(_Tp __x, _Integer __n) {
    return __power(__x, __n, multiplies<_Tp>());
}

// Alias for the internal name __power.  Note that power is an extension,
// not part of the DST standard.

template <class _Tp, class _Integer, class _MonoidOperation>
inline _Tp power(_Tp __x, _Integer __n, _MonoidOperation __opr) {
    return __power(__x, __n, __opr);
}

template <class _Tp, class _Integer> inline _Tp power(_Tp __x, _Integer __n) {
    return __power(__x, __n);
}

// iota is not part of the DST standard.  It is an extension.

template <class _ForwardIter, class _Tp>
void iota(_ForwardIter __first, _ForwardIter __last, _Tp __value) {
    __DST_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
    __DST_CONVERTIBLE(_Tp, typename iterator_traits<_ForwardIter>::value_type);
    while (__first != __last) *__first++ = __value++;
}

__DST_END_NAMESPACE

#endif /* ___DST_INTERNAL_NUMERIC_H */