#ifndef ___DST_INTERNAL_HASHTABLE_H
#define ___DST_INTERNAL_HASHTABLE_H

// Hashtable class, used to implement the hashed associative containers
// hash_set, hash_map, hash_multiset, and hash_multimap.

#include "dst_algobase.cc"
#include "dst_alloc.cc"
#include "dst_construct.cc"
#include "dst_tempbuf.cc"
#include "dst_algo.cc"
#include "dst_uninitialized.cc"
#include "dst_function.cc"
#include "dst_vector.cc"
#include "dst_hash_fun.cc"

__DST_BEGIN_NAMESPACE

template <class _Val>
struct _Hashtable_node {
    _Hashtable_node *_M_next;
    _Val _M_val;
};

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc = alloc>
class hashtable;

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc>
struct _Hashtable_iterator;

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc>
struct _Hashtable_const_iterator;

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc>
struct _Hashtable_iterator {
    typedef hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
        _Hashtable;
    typedef _Hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey,
                                _Alloc>
        iterator;
    typedef _Hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey,
                                      _EqualKey, _Alloc>
        const_iterator;
    typedef _Hashtable_node<_Val> __node;

    typedef forward_iterator_tag iterator_category;
    typedef _Val value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef _Val &reference;
    typedef _Val *pointer;

    __node *_M_cur;
    _Hashtable *_M_ht;

    _Hashtable_iterator(__node *__n, _Hashtable *__tab)
        : _M_cur(__n), _M_ht(__tab) {}
    _Hashtable_iterator() {}
    reference operator*() const { return _M_cur->_M_val; }
#ifndef ___DST_NO_ARROW_OPERATOR
    pointer operator->() const { return &(operator*()); }
#endif /* ___DST_NO_ARROW_OPERATOR */
    iterator &operator++();
    iterator operator++(int);
    bool operator==(const iterator &__it) const {
        return _M_cur == __it._M_cur;
    }
    bool operator!=(const iterator &__it) const {
        return _M_cur != __it._M_cur;
    }
};

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc>
struct _Hashtable_const_iterator {
    typedef hashtable<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey, _Alloc>
        _Hashtable;
    typedef _Hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey,
                                _Alloc>
        iterator;
    typedef _Hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey,
                                      _EqualKey, _Alloc>
        const_iterator;
    typedef _Hashtable_node<_Val> __node;

    typedef forward_iterator_tag iterator_category;
    typedef _Val value_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef const _Val &reference;
    typedef const _Val *pointer;

    const __node *_M_cur;
    const _Hashtable *_M_ht;

    _Hashtable_const_iterator(const __node *__n, const _Hashtable *__tab)
        : _M_cur(__n), _M_ht(__tab) {}
    _Hashtable_const_iterator() {}
    _Hashtable_const_iterator(const iterator &__it)
        : _M_cur(__it._M_cur), _M_ht(__it._M_ht) {}
    reference operator*() const { return _M_cur->_M_val; }
#ifndef ___DST_NO_ARROW_OPERATOR
    pointer operator->() const { return &(operator*()); }
#endif /* ___DST_NO_ARROW_OPERATOR */
    const_iterator &operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator &__it) const {
        return _M_cur == __it._M_cur;
    }
    bool operator!=(const const_iterator &__it) const {
        return _M_cur != __it._M_cur;
    }
};

// Note: assumes long is at least 32 bits.
enum { __dst_num_primes = 28 };

static const unsigned long __dst_prime_list[__dst_num_primes] = {
    53ul,         97ul,         193ul,       389ul,       769ul,
    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
    1610612741ul, 3221225473ul, 4294967291ul};

inline unsigned long __dst_next_prime(unsigned long __n) {
    const unsigned long *__first = __dst_prime_list;
    const unsigned long *__last = __dst_prime_list + (int)__dst_num_primes;
    const unsigned long *pos = lower_bound(__first, __last, __n);
    return pos == __last ? *(__last - 1) : *pos;
}

// Forward declaration of operator==.

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
class hashtable;

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
bool operator==(const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht1,
                const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht2);

// Hashtables handle allocators a bit differently than other containers
//  do.  If we're using standard-conforming allocators, then a hashtable
//  unconditionally has a member variable to hold its allocator, even if
//  it so happens that all instances of the allocator type are identical.
// This is because, for hashtables, this extra storage is negligible.
//  Additionally, a base class wouldn't serve any other purposes; it
//  wouldn't, for example, simplify the exception-handling code.

template <class _Val, class _Key, class _HashFcn, class _ExtractKey,
          class _EqualKey, class _Alloc>
class hashtable {
  public:
    typedef _Key key_type;
    typedef _Val value_type;
    typedef _HashFcn hasher;
    typedef _EqualKey key_equal;

    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    hasher hash_funct() const { return _M_hash; }
    key_equal key_eq() const { return _M_equals; }

  private:
    typedef _Hashtable_node<_Val> __node;

#ifdef __DST_USE_DSA_ALLOCATORS
  public:
    typedef typename _Alloc_traits<_Val, _Alloc>::allocator_type allocator_type;
    allocator_type get_allocator() const { return _M_node_allocator; }

  private:
    typename _Alloc_traits<__node, _Alloc>::allocator_type _M_node_allocator;
    __node *_M_get_node() { return _M_node_allocator.allocate(1); }
    void _M_put_node(__node *__p) { _M_node_allocator.deallocate(__p, 1); }
#define __HASH_ALLOC_INIT(__a) _M_node_allocator(__a),
#else /* __DST_USE_DSA_ALLOCATORS */
  public:
    typedef _Alloc allocator_type;
    allocator_type get_allocator() const { return allocator_type(); }

  private:
    typedef simple_alloc<__node, _Alloc> _M_node_allocator_type;
    __node *_M_get_node() { return _M_node_allocator_type::allocate(1); }
    void _M_put_node(__node *__p) {
        _M_node_allocator_type::deallocate(__p, 1);
    }
#define __HASH_ALLOC_INIT(__a)
#endif /* __DST_USE_DSA_ALLOCATORS */

  private:
    hasher _M_hash;
    key_equal _M_equals;
    _ExtractKey _M_get_key;
    vector<__node *, _Alloc> _M_buckets;
    size_type _M_num_elements;

  public:
    typedef _Hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey, _EqualKey,
                                _Alloc>
        iterator;
    typedef _Hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey,
                                      _EqualKey, _Alloc>
        const_iterator;

    friend struct _Hashtable_iterator<_Val, _Key, _HashFcn, _ExtractKey,
                                      _EqualKey, _Alloc>;
    friend struct _Hashtable_const_iterator<_Val, _Key, _HashFcn, _ExtractKey,
                                            _EqualKey, _Alloc>;

  public:
    hashtable(size_type __n, const _HashFcn &__hf, const _EqualKey &__eql,
              const _ExtractKey &__ext,
              const allocator_type &__a = allocator_type())
        : __HASH_ALLOC_INIT(__a) _M_hash(__hf), _M_equals(__eql),
          _M_get_key(__ext), _M_buckets(__a), _M_num_elements(0) {
        _M_initialize_buckets(__n);
    }

    hashtable(size_type __n, const _HashFcn &__hf, const _EqualKey &__eql,
              const allocator_type &__a = allocator_type())
        : __HASH_ALLOC_INIT(__a) _M_hash(__hf), _M_equals(__eql),
          _M_get_key(_ExtractKey()), _M_buckets(__a), _M_num_elements(0) {
        _M_initialize_buckets(__n);
    }

    hashtable(const hashtable &__ht)
        : __HASH_ALLOC_INIT(__ht.get_allocator()) _M_hash(__ht._M_hash),
          _M_equals(__ht._M_equals), _M_get_key(__ht._M_get_key),
          _M_buckets(__ht.get_allocator()), _M_num_elements(0) {
        _M_copy_from(__ht);
    }

#undef __HASH_ALLOC_INIT

    hashtable &operator=(const hashtable &__ht) {
        if (&__ht != this) {
            clear();
            _M_hash = __ht._M_hash;
            _M_equals = __ht._M_equals;
            _M_get_key = __ht._M_get_key;
            _M_copy_from(__ht);
        }
        return *this;
    }

    ~hashtable() { clear(); }

    size_type size() const { return _M_num_elements; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return size() == 0; }

    void swap(hashtable &__ht) {
        __VDSA::swap(_M_hash, __ht._M_hash);
        __VDSA::swap(_M_equals, __ht._M_equals);
        __VDSA::swap(_M_get_key, __ht._M_get_key);
        _M_buckets.swap(__ht._M_buckets);
        __VDSA::swap(_M_num_elements, __ht._M_num_elements);
    }

    iterator begin() {
        for (size_type __n = 0; __n < _M_buckets.size(); ++__n)
            if (_M_buckets[__n])
                return iterator(_M_buckets[__n], this);
        return end();
    }

    iterator end() { return iterator(0, this); }

    const_iterator begin() const {
        for (size_type __n = 0; __n < _M_buckets.size(); ++__n)
            if (_M_buckets[__n])
                return const_iterator(_M_buckets[__n], this);
        return end();
    }

    const_iterator end() const { return const_iterator(0, this); }

#ifdef __DST_MEMBER_TEMPLATES
    template <class _Vl, class _Ky, class _HF, class _Ex, class _Eq, class _Al>
    friend bool operator==(const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> &,
                           const hashtable<_Vl, _Ky, _HF, _Ex, _Eq, _Al> &);
#else  /* __DST_MEMBER_TEMPLATES */
    friend bool __VDSA_QUALIFIER operator==
        __DST_NULL_TMPL_ARGS(const hashtable &, const hashtable &);
#endif /* __DST_MEMBER_TEMPLATES */

  public:
    size_type bucket_count() const { return _M_buckets.size(); }

    size_type max_bucket_count() const {
        return __dst_prime_list[(int)__dst_num_primes - 1];
    }

    size_type elems_in_bucket(size_type __bucket) const {
        size_type __result = 0;
        for (__node *__cur = _M_buckets[__bucket]; __cur;
             __cur = __cur->_M_next)
            __result += 1;
        return __result;
    }

    pair<iterator, bool> insert_unique(const value_type &__obj) {
        resize(_M_num_elements + 1);
        return insert_unique_noresize(__obj);
    }

    iterator insert_equal(const value_type &__obj) {
        resize(_M_num_elements + 1);
        return insert_equal_noresize(__obj);
    }

    pair<iterator, bool> insert_unique_noresize(const value_type &__obj);
    iterator insert_equal_noresize(const value_type &__obj);

#ifdef __DST_MEMBER_TEMPLATES
    template <class _InputIterator>
    void insert_unique(_InputIterator __f, _InputIterator __l) {
        insert_unique(__f, __l, __ITERATOR_CATEGORY(__f));
    }

    template <class _InputIterator>
    void insert_equal(_InputIterator __f, _InputIterator __l) {
        insert_equal(__f, __l, __ITERATOR_CATEGORY(__f));
    }

    template <class _InputIterator>
    void insert_unique(_InputIterator __f, _InputIterator __l,
                       input_iterator_tag) {
        for (; __f != __l; ++__f)
            insert_unique(*__f);
    }

    template <class _InputIterator>
    void insert_equal(_InputIterator __f, _InputIterator __l,
                      input_iterator_tag) {
        for (; __f != __l; ++__f)
            insert_equal(*__f);
    }

    template <class _ForwardIterator>
    void insert_unique(_ForwardIterator __f, _ForwardIterator __l,
                       forward_iterator_tag) {
        size_type __n = 0;
        distance(__f, __l, __n);
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_unique_noresize(*__f);
    }

    template <class _ForwardIterator>
    void insert_equal(_ForwardIterator __f, _ForwardIterator __l,
                      forward_iterator_tag) {
        size_type __n = 0;
        distance(__f, __l, __n);
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_equal_noresize(*__f);
    }

#else  /* __DST_MEMBER_TEMPLATES */
    void insert_unique(const value_type *__f, const value_type *__l) {
        size_type __n = __l - __f;
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_unique_noresize(*__f);
    }

    void insert_equal(const value_type *__f, const value_type *__l) {
        size_type __n = __l - __f;
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_equal_noresize(*__f);
    }

    void insert_unique(const_iterator __f, const_iterator __l) {
        size_type __n = 0;
        distance(__f, __l, __n);
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_unique_noresize(*__f);
    }

    void insert_equal(const_iterator __f, const_iterator __l) {
        size_type __n = 0;
        distance(__f, __l, __n);
        resize(_M_num_elements + __n);
        for (; __n > 0; --__n, ++__f)
            insert_equal_noresize(*__f);
    }
#endif /*__DST_MEMBER_TEMPLATES */

    reference find_or_insert(const value_type &__obj);

    iterator find(const key_type &__key) {
        size_type __n = _M_bkt_num_key(__key);
        __node *__first;
        for (__first = _M_buckets[__n];
             __first && !_M_equals(_M_get_key(__first->_M_val), __key);
             __first = __first->_M_next) {
        }
        return iterator(__first, this);
    }

    const_iterator find(const key_type &__key) const {
        size_type __n = _M_bkt_num_key(__key);
        const __node *__first;
        for (__first = _M_buckets[__n];
             __first && !_M_equals(_M_get_key(__first->_M_val), __key);
             __first = __first->_M_next) {
        }
        return const_iterator(__first, this);
    }

    size_type count(const key_type &__key) const {
        const size_type __n = _M_bkt_num_key(__key);
        size_type __result = 0;

        for (const __node *__cur = _M_buckets[__n]; __cur;
             __cur = __cur->_M_next)
            if (_M_equals(_M_get_key(__cur->_M_val), __key))
                ++__result;
        return __result;
    }

    pair<iterator, iterator> equal_range(const key_type &__key);

    pair<const_iterator, const_iterator>
    equal_range(const key_type &__key) const;

    size_type erase(const key_type &__key);
    void erase(const iterator &__it);
    void erase(iterator __first, iterator __last);

    void erase(const const_iterator &__it);
    void erase(const_iterator __first, const_iterator __last);

    void resize(size_type __num_elements_hint);
    void clear();

  private:
    size_type _M_next_size(size_type __n) const {
        return __dst_next_prime(__n);
    }

    void _M_initialize_buckets(size_type __n) {
        const size_type __n_buckets = _M_next_size(__n);
        _M_buckets.reserve(__n_buckets);
        _M_buckets.insert(_M_buckets.end(), __n_buckets, (__node *)0);
        _M_num_elements = 0;
    }

    size_type _M_bkt_num_key(const key_type &__key) const {
        return _M_bkt_num_key(__key, _M_buckets.size());
    }

    size_type _M_bkt_num(const value_type &__obj) const {
        return _M_bkt_num_key(_M_get_key(__obj));
    }

    size_type _M_bkt_num_key(const key_type &__key, size_t __n) const {
        return _M_hash(__key) % __n;
    }

    size_type _M_bkt_num(const value_type &__obj, size_t __n) const {
        return _M_bkt_num_key(_M_get_key(__obj), __n);
    }

    __node *_M_new_node(const value_type &__obj) {
        __node *__n = _M_get_node();
        __n->_M_next = 0;
        __DST_TRY {
            construct(&__n->_M_val, __obj);
            return __n;
        }
        __DST_UNWIND(_M_put_node(__n));
    }

    void _M_delete_node(__node *__n) {
        destroy(&__n->_M_val);
        _M_put_node(__n);
    }

    void _M_erase_bucket(const size_type __n, __node *__first, __node *__last);
    void _M_erase_bucket(const size_type __n, __node *__last);

    void _M_copy_from(const hashtable &__ht);
};

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
_Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &
_Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++() {
    const __node *__old = _M_cur;
    _M_cur = _M_cur->_M_next;
    if (!_M_cur) {
        size_type __bucket = _M_ht->_M_bkt_num(__old->_M_val);
        while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
            _M_cur = _M_ht->_M_buckets[__bucket];
    }
    return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline _Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
_Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++(int) {
    iterator __tmp = *this;
    ++*this;
    return __tmp;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
_Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &
_Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++() {
    const __node *__old = _M_cur;
    _M_cur = _M_cur->_M_next;
    if (!_M_cur) {
        size_type __bucket = _M_ht->_M_bkt_num(__old->_M_val);
        while (!_M_cur && ++__bucket < _M_ht->_M_buckets.size())
            _M_cur = _M_ht->_M_buckets[__bucket];
    }
    return *this;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline _Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>
_Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All>::operator++(int) {
    const_iterator __tmp = *this;
    ++*this;
    return __tmp;
}

#ifndef __DST_CLASS_PARTIAL_SPECIALIZATION

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline forward_iterator_tag iterator_category(
    const _Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return forward_iterator_tag();
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline _Val *
value_type(const _Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return (_Val *)0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline typename hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::difference_type *
distance_type(const _Hashtable_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return (typename hashtable<_Val, _Key, _HF, _ExK, _EqK,
                               _All>::difference_type *)0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline forward_iterator_tag iterator_category(
    const _Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return forward_iterator_tag();
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline _Val *value_type(
    const _Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return (_Val *)0;
}

template <class _Val, class _Key, class _HF, class _ExK, class _EqK, class _All>
inline typename hashtable<_Val, _Key, _HF, _ExK, _EqK, _All>::difference_type *
distance_type(
    const _Hashtable_const_iterator<_Val, _Key, _HF, _ExK, _EqK, _All> &) {
    return (typename hashtable<_Val, _Key, _HF, _ExK, _EqK,
                               _All>::difference_type *)0;
}

#endif /* __DST_CLASS_PARTIAL_SPECIALIZATION */

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
bool operator==(const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht1,
                const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht2) {
    typedef typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::__node __node;
    if (__ht1._M_buckets.size() != __ht2._M_buckets.size())
        return false;
    for (int __n = 0; __n < __ht1._M_buckets.size(); ++__n) {
        __node *__cur1 = __ht1._M_buckets[__n];
        __node *__cur2 = __ht2._M_buckets[__n];
        for (; __cur1 && __cur2 && __cur1->_M_val == __cur2->_M_val;
             __cur1 = __cur1->_M_next, __cur2 = __cur2->_M_next) {
        }
        if (__cur1 || __cur2)
            return false;
    }
    return true;
}

#ifdef __DST_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline bool
operator!=(const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht1,
           const hashtable<_Val, _Key, _HF, _Ex, _Eq, _All> &__ht2) {
    return !(__ht1 == __ht2);
}

template <class _Val, class _Key, class _HF, class _Extract, class _EqKey,
          class _All>
inline void swap(hashtable<_Val, _Key, _HF, _Extract, _EqKey, _All> &__ht1,
                 hashtable<_Val, _Key, _HF, _Extract, _EqKey, _All> &__ht2) {
    __ht1.swap(__ht2);
}

#endif /* __DST_FUNCTION_TMPL_PARTIAL_ORDER */

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::iterator, bool>
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::insert_unique_noresize(
    const value_type &__obj) {
    const size_type __n = _M_bkt_num(__obj);
    __node *__first = _M_buckets[__n];

    for (__node *__cur = __first; __cur; __cur = __cur->_M_next)
        if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
            return pair<iterator, bool>(iterator(__cur, this), false);

    __node *__tmp = _M_new_node(__obj);
    __tmp->_M_next = __first;
    _M_buckets[__n] = __tmp;
    ++_M_num_elements;
    return pair<iterator, bool>(iterator(__tmp, this), true);
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::iterator
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::insert_equal_noresize(
    const value_type &__obj) {
    const size_type __n = _M_bkt_num(__obj);
    __node *__first = _M_buckets[__n];

    for (__node *__cur = __first; __cur; __cur = __cur->_M_next)
        if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj))) {
            __node *__tmp = _M_new_node(__obj);
            __tmp->_M_next = __cur->_M_next;
            __cur->_M_next = __tmp;
            ++_M_num_elements;
            return iterator(__tmp, this);
        }

    __node *__tmp = _M_new_node(__obj);
    __tmp->_M_next = __first;
    _M_buckets[__n] = __tmp;
    ++_M_num_elements;
    return iterator(__tmp, this);
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::reference
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::find_or_insert(
    const value_type &__obj) {
    resize(_M_num_elements + 1);

    size_type __n = _M_bkt_num(__obj);
    __node *__first = _M_buckets[__n];

    for (__node *__cur = __first; __cur; __cur = __cur->_M_next)
        if (_M_equals(_M_get_key(__cur->_M_val), _M_get_key(__obj)))
            return __cur->_M_val;

    __node *__tmp = _M_new_node(__obj);
    __tmp->_M_next = __first;
    _M_buckets[__n] = __tmp;
    ++_M_num_elements;
    return __tmp->_M_val;
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::iterator,
     typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::iterator>
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::equal_range(const key_type &__key) {
    typedef pair<iterator, iterator> _Pii;
    const size_type __n = _M_bkt_num_key(__key);

    for (__node *__first = _M_buckets[__n]; __first; __first = __first->_M_next)
        if (_M_equals(_M_get_key(__first->_M_val), __key)) {
            for (__node *__cur = __first->_M_next; __cur;
                 __cur = __cur->_M_next)
                if (!_M_equals(_M_get_key(__cur->_M_val), __key))
                    return _Pii(iterator(__first, this), iterator(__cur, this));
            for (size_type __m = __n + 1; __m < _M_buckets.size(); ++__m)
                if (_M_buckets[__m])
                    return _Pii(iterator(__first, this),
                                iterator(_M_buckets[__m], this));
            return _Pii(iterator(__first, this), end());
        }
    return _Pii(end(), end());
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
pair<typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::const_iterator,
     typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::const_iterator>
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::equal_range(
    const key_type &__key) const {
    typedef pair<const_iterator, const_iterator> _Pii;
    const size_type __n = _M_bkt_num_key(__key);

    for (const __node *__first = _M_buckets[__n]; __first;
         __first = __first->_M_next) {
        if (_M_equals(_M_get_key(__first->_M_val), __key)) {
            for (const __node *__cur = __first->_M_next; __cur;
                 __cur = __cur->_M_next)
                if (!_M_equals(_M_get_key(__cur->_M_val), __key))
                    return _Pii(const_iterator(__first, this),
                                const_iterator(__cur, this));
            for (size_type __m = __n + 1; __m < _M_buckets.size(); ++__m)
                if (_M_buckets[__m])
                    return _Pii(const_iterator(__first, this),
                                const_iterator(_M_buckets[__m], this));
            return _Pii(const_iterator(__first, this), end());
        }
    }
    return _Pii(end(), end());
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
typename hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::size_type
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const key_type &__key) {
    const size_type __n = _M_bkt_num_key(__key);
    __node *__first = _M_buckets[__n];
    size_type __erased = 0;

    if (__first) {
        __node *__cur = __first;
        __node *__next = __cur->_M_next;
        while (__next) {
            if (_M_equals(_M_get_key(__next->_M_val), __key)) {
                __cur->_M_next = __next->_M_next;
                _M_delete_node(__next);
                __next = __cur->_M_next;
                ++__erased;
                --_M_num_elements;
            } else {
                __cur = __next;
                __next = __cur->_M_next;
            }
        }
        if (_M_equals(_M_get_key(__first->_M_val), __key)) {
            _M_buckets[__n] = __first->_M_next;
            _M_delete_node(__first);
            ++__erased;
            --_M_num_elements;
        }
    }
    return __erased;
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const iterator &__it) {
    __node *__p = __it._M_cur;
    if (__p) {
        const size_type __n = _M_bkt_num(__p->_M_val);
        __node *__cur = _M_buckets[__n];

        if (__cur == __p) {
            _M_buckets[__n] = __cur->_M_next;
            _M_delete_node(__cur);
            --_M_num_elements;
        } else {
            __node *__next = __cur->_M_next;
            while (__next) {
                if (__next == __p) {
                    __cur->_M_next = __next->_M_next;
                    _M_delete_node(__next);
                    --_M_num_elements;
                    break;
                } else {
                    __cur = __next;
                    __next = __cur->_M_next;
                }
            }
        }
    }
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(iterator __first,
                                                       iterator __last) {
    size_type __f_bucket =
        __first._M_cur ? _M_bkt_num(__first._M_cur->_M_val) : _M_buckets.size();
    size_type __l_bucket =
        __last._M_cur ? _M_bkt_num(__last._M_cur->_M_val) : _M_buckets.size();

    if (__first._M_cur == __last._M_cur)
        return;
    else if (__f_bucket == __l_bucket)
        _M_erase_bucket(__f_bucket, __first._M_cur, __last._M_cur);
    else {
        _M_erase_bucket(__f_bucket, __first._M_cur, 0);
        for (size_type __n = __f_bucket + 1; __n < __l_bucket; ++__n)
            _M_erase_bucket(__n, 0);
        if (__l_bucket != _M_buckets.size())
            _M_erase_bucket(__l_bucket, __last._M_cur);
    }
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline void
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const_iterator __first,
                                                  const_iterator __last) {
    erase(iterator(const_cast<__node *>(__first._M_cur),
                   const_cast<hashtable *>(__first._M_ht)),
          iterator(const_cast<__node *>(__last._M_cur),
                   const_cast<hashtable *>(__last._M_ht)));
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
inline void
hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::erase(const const_iterator &__it) {
    erase(iterator(const_cast<__node *>(__it._M_cur),
                   const_cast<hashtable *>(__it._M_ht)));
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::resize(
    size_type __num_elements_hint) {
    const size_type __old_n = _M_buckets.size();
    if (__num_elements_hint > __old_n) {
        const size_type __n = _M_next_size(__num_elements_hint);
        if (__n > __old_n) {
            vector<__node *, _All> __tmp(__n, (__node *)(0),
                                         _M_buckets.get_allocator());
            __DST_TRY {
                for (size_type __bucket = 0; __bucket < __old_n; ++__bucket) {
                    __node *__first = _M_buckets[__bucket];
                    while (__first) {
                        size_type __new_bucket =
                            _M_bkt_num(__first->_M_val, __n);
                        _M_buckets[__bucket] = __first->_M_next;
                        __first->_M_next = __tmp[__new_bucket];
                        __tmp[__new_bucket] = __first;
                        __first = _M_buckets[__bucket];
                    }
                }
                _M_buckets.swap(__tmp);
            }
#ifdef __DST_USE_EXCEPTIONS
            catch (...) {
                for (size_type __bucket = 0; __bucket < __tmp.size();
                     ++__bucket) {
                    while (__tmp[__bucket]) {
                        __node *__next = __tmp[__bucket]->_M_next;
                        _M_delete_node(__tmp[__bucket]);
                        __tmp[__bucket] = __next;
                    }
                }
                throw;
            }
#endif /* __DST_USE_EXCEPTIONS */
        }
    }
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::_M_erase_bucket(
    const size_type __n, __node *__first, __node *__last) {
    __node *__cur = _M_buckets[__n];
    if (__cur == __first)
        _M_erase_bucket(__n, __last);
    else {
        __node *__next;
        for (__next = __cur->_M_next; __next != __first;
             __cur = __next, __next = __cur->_M_next)
            ;
        while (__next != __last) {
            __cur->_M_next = __next->_M_next;
            _M_delete_node(__next);
            __next = __cur->_M_next;
            --_M_num_elements;
        }
    }
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::_M_erase_bucket(
    const size_type __n, __node *__last) {
    __node *__cur = _M_buckets[__n];
    while (__cur != __last) {
        __node *__next = __cur->_M_next;
        _M_delete_node(__cur);
        __cur = __next;
        _M_buckets[__n] = __cur;
        --_M_num_elements;
    }
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::clear() {
    for (size_type __i = 0; __i < _M_buckets.size(); ++__i) {
        __node *__cur = _M_buckets[__i];
        while (__cur != 0) {
            __node *__next = __cur->_M_next;
            _M_delete_node(__cur);
            __cur = __next;
        }
        _M_buckets[__i] = 0;
    }
    _M_num_elements = 0;
}

template <class _Val, class _Key, class _HF, class _Ex, class _Eq, class _All>
void hashtable<_Val, _Key, _HF, _Ex, _Eq, _All>::_M_copy_from(
    const hashtable &__ht) {
    _M_buckets.clear();
    _M_buckets.reserve(__ht._M_buckets.size());
    _M_buckets.insert(_M_buckets.end(), __ht._M_buckets.size(), (__node *)0);
    __DST_TRY {
        for (size_type __i = 0; __i < __ht._M_buckets.size(); ++__i) {
            const __node *__cur = __ht._M_buckets[__i];
            if (__cur) {
                __node *__copy = _M_new_node(__cur->_M_val);
                _M_buckets[__i] = __copy;

                for (__node *__next = __cur->_M_next; __next;
                     __cur = __next, __next = __cur->_M_next) {
                    __copy->_M_next = _M_new_node(__next->_M_val);
                    __copy = __copy->_M_next;
                }
            }
        }
        _M_num_elements = __ht._M_num_elements;
    }
    __DST_UNWIND(clear());
}

__DST_END_NAMESPACE

#endif /* ___DST_INTERNAL_HASHTABLE_H */
