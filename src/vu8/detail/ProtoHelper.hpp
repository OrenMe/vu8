#ifndef BOOST_PP_IS_ITERATING
#   ifndef TSA_VU8_DETAIL_PROTO_HELPER_HPP
#   define TSA_VU8_DETAIL_PROTO_HELPER_HPP
#       include <vu8/config.hpp>

#       include <boost/preprocessor/repetition.hpp>
#       include <boost/preprocessor/arithmetic/sub.hpp>
#       include <boost/preprocessor/punctuation/comma_if.hpp>
#       include <boost/preprocessor/iteration/iterate.hpp>
#       include <boost/mpl/vector.hpp>

#       ifndef VU8_PROTO_MAX_SIZE
#         define VU8_PROTO_MAX_SIZE VU8_PP_ITERATION_LIMIT
#       endif
namespace vu8 { namespace detail {

namespace mpl = boost::mpl;

template <class R>
struct FunProtoBase {
    typedef R return_type;
};

template <class T>
struct FunProto;

template <class C, class T>
struct MemFunProto;

} }
#       define BOOST_PP_ITERATION_LIMITS (0, VU8_PROTO_MAX_SIZE - 1)
#       define BOOST_PP_FILENAME_1       "vu8/detail/ProtoHelper.hpp"
#       include BOOST_PP_ITERATE()
#    endif // include guard
#else // BOOST_PP_IS_ITERATING

#   define n BOOST_PP_ITERATION()
#   define VU8_PROTO_print(z, n, data) data

namespace vu8 { namespace detail {

template <class R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
struct FunProto<R ( BOOST_PP_ENUM_PARAMS(n, A) )> : FunProtoBase<R> {
    typedef mpl::vector<BOOST_PP_ENUM_PARAMS(n, A)>   arguments;
    typedef R(*function_type)(BOOST_PP_ENUM_PARAMS(n, A));
};

template <class C, class R BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>
struct MemFunProto<C, R ( BOOST_PP_ENUM_PARAMS(n, A) )> : FunProtoBase<R> {
    typedef mpl::vector<BOOST_PP_ENUM_PARAMS(n, A)>   arguments;
    typedef R(C::*method_type)(BOOST_PP_ENUM_PARAMS(n, A));
};

} }

#   undef n

#endif
