

#ifndef ___DST_MEMORY
#define ___DST_MEMORY

#include "dst_algobase.cc"
#include "dst_alloc.cc"
#include "dst_construct.cc"
#include "dst_tempbuf.cc"
#include "dst_uninitialized.cc"
#include "dst_raw_storage_iter.cc"

__DST_BEGIN_NAMESPACE

#if defined(___DST_USE_AUTO_PTR_CONVERSIONS) && defined(__DST_MEMBER_TEMPLATES)

template <class _Tp1>
struct auto_ptr_ref {
    _Tp1 *__ptr_;
    auto_ptr_ref(_Tp1 *_p) : __ptr_(_p) {}
};

#endif

template <class _Tp>
class auto_ptr {
  private:
    _Tp *__ptr_;

  public:
    typedef _Tp element_type;

    explicit auto_ptr(_Tp *_p = 0) __DST_NOTHROW : __ptr_(_p) {}
    auto_ptr(auto_ptr &__a) __DST_NOTHROW : __ptr_(__a.release()) {}

#ifdef __DST_MEMBER_TEMPLATES
    template <class _Tp1>
    auto_ptr(auto_ptr<_Tp1> &__a) __DST_NOTHROW : __ptr_(__a.release()) {}
#endif /* __DST_MEMBER_TEMPLATES */

    auto_ptr &operator=(auto_ptr &__a) __DST_NOTHROW {
        if (&__a != this) {
            delete __ptr_;
            __ptr_ = __a.release();
        }
        return *this;
    }

#ifdef __DST_MEMBER_TEMPLATES
    template <class _Tp1>
    auto_ptr &operator=(auto_ptr<_Tp1> &__a) __DST_NOTHROW {
        if (__a.get() != this->get()) {
            delete __ptr_;
            __ptr_ = __a.release();
        }
        return *this;
    }
#endif /* __DST_MEMBER_TEMPLATES */

    // Note: The DST standard says there is supposed to be an empty throw
    // specification here, but omitting it is standard conforming.  Its
    // presence can be detected only if _Tp::~_Tp() throws, but (17.4.3.6/2)
    // this is prohibited.
    ~auto_ptr() { delete __ptr_; }

    _Tp &operator*() const __DST_NOTHROW { return *__ptr_; }
    _Tp *operator->() const __DST_NOTHROW { return __ptr_; }
    _Tp *get() const __DST_NOTHROW { return __ptr_; }
    _Tp *release() __DST_NOTHROW {
        _Tp *__tmp = __ptr_;
        __ptr_ = 0;
        return __tmp;
    }
    void reset(_Tp *_p = 0) __DST_NOTHROW {
        if (_p != __ptr_) {
            delete __ptr_;
            __ptr_ = _p;
        }
    }

    // According to the DST standard, these conversions are required.  Most
    // present-day compilers, however, do not enforce that requirement---and,
    // in fact, most present-day compilers do not support the language
    // features that these conversions rely on.

#if defined(___DST_USE_AUTO_PTR_CONVERSIONS) && defined(__DST_MEMBER_TEMPLATES)

  public:
    auto_ptr(auto_ptr_ref<_Tp> __ref) __DST_NOTHROW : __ptr_(__ref.__ptr_) {}

    auto_ptr &operator=(auto_ptr_ref<_Tp> __ref) __DST_NOTHROW {
        if (__ref.__ptr_ != this->get()) {
            delete __ptr_;
            __ptr_ = __ref.__ptr_;
        }
        return *this;
    }

    template <class _Tp1>
    operator auto_ptr_ref<_Tp1>() __DST_NOTHROW {
        return auto_ptr_ref<_Tp1>(this->release());
    }
    template <class _Tp1>
    operator auto_ptr<_Tp1>() __DST_NOTHROW {
        return auto_ptr<_Tp1>(this->release());
    }

#endif /* auto ptr conversions && member templates */
};

__DST_END_NAMESPACE

#endif /* ___DST_MEMORY */
