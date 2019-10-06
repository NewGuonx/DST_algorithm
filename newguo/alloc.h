
#ifndef ___DST_ALLOC_H
#define ___DST_ALLOC_H

#ifndef __DST_CONFIG_H
#include "dst_config.h"
#endif
#ifndef ___DST_INTERNAL_ALLOC_H
#include "dst_alloc.h"
#endif

#ifdef __DST_USE_NAMESPACES

using __DSA::__default_alloc_template;
using __DSA::__malloc_alloc_template;
using __DSA::alloc;
using __DSA::debug_alloc;
using __DSA::malloc_alloc;
using __DSA::simple_alloc;
using __DSA::single_client_alloc;
#ifdef __DST_STATIC_TEMPLATE_MEMBER_BUG
using __DSA::__malloc_alloc_oom_handler;
#endif /* __DST_STATIC_TEMPLATE_MEMBER_BUG */
#ifdef __DST_USE_DSA_ALLOCATORS
using __DSA::allocator;
#endif /* __DST_USE_DSA_ALLOCATORS */

#endif /* __DST_USE_NAMESPACES */

#endif /* ___DST_ALLOC_H */

// Local Variables:
// mode:C++
// End:
