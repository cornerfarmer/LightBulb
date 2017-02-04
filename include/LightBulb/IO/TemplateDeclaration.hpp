#pragma once

#ifndef _TEMPLATEDECLARATION_H_
#define _TEMPLATEDECLARATION_H_

#include "LightBulb/IO/UsedArchives.hpp"

#define DECLARE_SINGLE_SERIALIZATION_TEMPLATE(T) \
template void serialize<cereal::JSONOutputArchive>(cereal::JSONOutputArchive &, T &); \
template void serialize<cereal::JSONInputArchive>(cereal::JSONInputArchive &, T &); \
template void serialize<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &, T &); \
template void serialize<cereal::XMLInputArchive>(cereal::XMLInputArchive &, T &); \
template void serialize<cereal::PortableBinaryOutputArchive>(cereal::PortableBinaryOutputArchive &, T &); \
template void serialize<cereal::PortableBinaryInputArchive>(cereal::PortableBinaryInputArchive &, T &);

#define DECLARE_SERIALIZATION_TEMPLATE(T) \
template void save<cereal::JSONOutputArchive>(cereal::JSONOutputArchive &, T const &); \
template void load<cereal::JSONInputArchive>(cereal::JSONInputArchive &, T &); \
template void save<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &, T const &); \
template void load<cereal::XMLInputArchive>(cereal::XMLInputArchive &, T &); \
template void save<cereal::PortableBinaryOutputArchive>(cereal::PortableBinaryOutputArchive &, T const &); \
template void load<cereal::PortableBinaryInputArchive>(cereal::PortableBinaryInputArchive &, T &);


#define DECLARE_LOAD_AND_CONSTRUCT_TEMPLATE(T) \
template void LoadAndConstruct<T>::load_and_construct<cereal::JSONInputArchive>(cereal::JSONInputArchive& , construct<T>&); \
template void LoadAndConstruct<T>::load_and_construct<cereal::XMLInputArchive>(cereal::XMLInputArchive& , construct<T>&); \
template void LoadAndConstruct<T>::load_and_construct<cereal::PortableBinaryInputArchive>(cereal::PortableBinaryInputArchive& , construct<T>&); 

#ifdef _MSC_VER
#   define CEREAL_DLL_IMPORT __declspec(dllexport)
#else // clang or gcc
#   define CEREAL_DLL_IMPORT
#endif

#define CEREAL_FORCE_DYNAMIC_INIT_FIXED(LibName)              \
  namespace cereal {                                    \
  namespace detail {                                    \
    CEREAL_DLL_IMPORT void dynamic_init_dummy_##LibName();                \
  } /* end detail */                                    \
  namespace {                                           \
    void dynamic_init_##LibName()                       \
    {                                                   \
      ::cereal::detail::dynamic_init_dummy_##LibName(); \
    }                                                   \
  } } /* end namespaces */

#endif