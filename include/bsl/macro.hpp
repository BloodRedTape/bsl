#pragma once

#define BSL_EXPAND(x) x
#define BSL_STRINGIFY(x) #x

#define BSL_CONCATENATE(x,y) x##y

#define BSL_FOR_EACH_1(what, x, ...) what(x)
#define BSL_FOR_EACH_2(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_1(what,  __VA_ARGS__))
#define BSL_FOR_EACH_3(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_2(what, __VA_ARGS__))
#define BSL_FOR_EACH_4(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_3(what,  __VA_ARGS__))
#define BSL_FOR_EACH_5(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_4(what,  __VA_ARGS__))
#define BSL_FOR_EACH_6(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_5(what,  __VA_ARGS__))
#define BSL_FOR_EACH_7(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_6(what,  __VA_ARGS__))
#define BSL_FOR_EACH_8(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_7(what,  __VA_ARGS__))
#define BSL_FOR_EACH_9(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_8(what,  __VA_ARGS__))
#define BSL_FOR_EACH_10(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_9(what,  __VA_ARGS__))
#define BSL_FOR_EACH_11(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_10(what,  __VA_ARGS__))
#define BSL_FOR_EACH_12(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_11(what,  __VA_ARGS__))
#define BSL_FOR_EACH_13(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_12(what,  __VA_ARGS__))
#define BSL_FOR_EACH_14(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_13(what,  __VA_ARGS__))
#define BSL_FOR_EACH_15(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_14(what,  __VA_ARGS__))
#define BSL_FOR_EACH_16(what, x, ...)\
  what(x)\
  BSL_EXPAND(BSL_FOR_EACH_15(what,  __VA_ARGS__))

#define BSL_FOR_EACH_NARG(...) BSL_FOR_EACH_NARG_(__VA_ARGS__, BSL_FOR_EACH_RSEQ_N())
#define BSL_FOR_EACH_NARG_(...) BSL_EXPAND(BSL_FOR_EACH_ARG_N(__VA_ARGS__))
#define BSL_FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define BSL_FOR_EACH_RSEQ_N() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define BSL_FOR_EACH_(N, what, ...) BSL_EXPAND(BSL_CONCATENATE(BSL_FOR_EACH_, N)(what, __VA_ARGS__))
#define BSL_FOR_EACH(what, ...) BSL_FOR_EACH_(BSL_FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)


#define BSL_FOR_EACH_INDEXED_1(what, x, ...) what(x, 0)
#define BSL_FOR_EACH_INDEXED_2(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_1_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_3(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_2_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_4(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_3_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_5(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_4_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_6(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_5_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_7(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_6_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_8(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_7_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_9(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_8_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_10(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_9_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_11(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_10_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_12(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_11_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_13(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_12_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_14(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_13_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_15(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_14_I(what, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_16(what, x, ...)\
  what(x, 0)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_15_I(what, 1, __VA_ARGS__))

// Helper macros to continue the indexing
#define BSL_FOR_EACH_INDEXED_1_I(what, idx, x, ...) what(x, idx)
#define BSL_FOR_EACH_INDEXED_2_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_1_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_3_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_2_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_4_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_3_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_5_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_4_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_6_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_5_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_7_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_6_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_8_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_7_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_9_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_8_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_10_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_9_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_11_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_10_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_12_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_11_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_13_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_12_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_14_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_13_I(what, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_15_I(what, idx, x, ...)\
  what(x, idx)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_14_I(what, idx+1, __VA_ARGS__))

#define BSL_FOR_EACH_INDEXED_(N, what, ...) BSL_EXPAND(BSL_CONCATENATE(BSL_FOR_EACH_INDEXED_, N)(what, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED(what, ...) BSL_FOR_EACH_INDEXED_(BSL_FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define BSL_FOR_EACH_INDEXED_PARAM_1(what, param, x, ...) what(x, 0, param)
#define BSL_FOR_EACH_INDEXED_PARAM_2(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_1_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_3(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_2_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_4(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_3_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_5(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_4_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_6(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_5_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_7(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_6_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_8(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_7_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_9(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_8_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_10(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_9_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_11(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_10_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_12(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_11_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_13(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_12_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_14(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_13_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_15(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_14_I(what, param, 1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_16(what, param, x, ...)\
  what(x, 0, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_15_I(what, param, 1, __VA_ARGS__))

// Helper macros to continue the indexing with parameter
#define BSL_FOR_EACH_INDEXED_PARAM_1_I(what, param, idx, x, ...) what(x, idx, param)
#define BSL_FOR_EACH_INDEXED_PARAM_2_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_1_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_3_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_2_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_4_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_3_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_5_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_4_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_6_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_5_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_7_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_6_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_8_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_7_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_9_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_8_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_10_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_9_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_11_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_10_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_12_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_11_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_13_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_12_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_14_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_13_I(what, param, idx+1, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM_15_I(what, param, idx, x, ...)\
  what(x, idx, param)\
  BSL_EXPAND(BSL_FOR_EACH_INDEXED_PARAM_14_I(what, param, idx+1, __VA_ARGS__))

#define BSL_FOR_EACH_INDEXED_PARAM_(N, what, param, ...) BSL_EXPAND(BSL_CONCATENATE(BSL_FOR_EACH_INDEXED_PARAM_, N)(what, param, __VA_ARGS__))
#define BSL_FOR_EACH_INDEXED_PARAM(what, param, ...) BSL_FOR_EACH_INDEXED_PARAM_(BSL_FOR_EACH_NARG(__VA_ARGS__), what, param, __VA_ARGS__)
