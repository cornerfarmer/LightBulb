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

#endif