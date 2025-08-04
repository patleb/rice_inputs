#pragma once

#define G_NONE   0
#define G_DOUBLE 1
#define G_INT64  2
#define G_UINT64 3
#define G_STRING 4

constexpr auto none = nullstate{};

using GType = std::variant< nullstate, int64_t2, double, uint64_t2, std::string >;

inline bool is_none(const GType & value) {
  return value.index() == 0;
}

template < class T >
inline T g_cast(const GType & value) {
  switch (value.index()) {
  case G_NONE:   return static_cast< T >(0);
  case G_DOUBLE: return static_cast< T >(std::get< G_DOUBLE >(value));
  case G_INT64:  return static_cast< T >(std::get< G_INT64 >(value));
  case G_UINT64: return static_cast< T >(std::get< G_UINT64 >(value));
  default: throw RuntimeError("invalid GType");
  }
}

template <>
inline float g_cast< float >(const GType & value) {
  switch (value.index()) {
  case G_NONE:   return static_cast< float >(Float::nan);
  case G_DOUBLE: return static_cast< float >(std::get< G_DOUBLE >(value));
  case G_INT64:  return static_cast< float >(std::get< G_INT64 >(value));
  case G_UINT64: return static_cast< float >(std::get< G_UINT64 >(value));
  default: throw RuntimeError("invalid GType");
  }
}

template <>
inline double g_cast< double >(const GType & value) {
  switch (value.index()) {
  case G_NONE:   return Float::nan;
  case G_DOUBLE: return std::get< G_DOUBLE >(value);
  case G_INT64:  return static_cast< double >(std::get< G_INT64 >(value));
  case G_UINT64: return static_cast< double >(std::get< G_UINT64 >(value));
  default: throw RuntimeError("invalid GType");
  }
}

inline auto g_cast(const Oint32_t & value) {
  return static_cast< int64_t2 >(value ? *value : 0);
}

inline auto g_cast(int32_t value) {
  return static_cast< int64_t2 >(value);
}

inline auto g_cast(const Oint64_t2 & value) {
  return static_cast< int64_t2 >(value ? *value : 0);
}

inline auto g_cast(int64_t2 value) {
  return static_cast< int64_t2 >(value);
}

inline auto g_cast(const Ofloat & value) {
  return value ? static_cast< double >(*value) : Float::nan;
}

inline auto g_cast(float value) {
  return static_cast< double >(value);
}

inline auto g_cast(const Odouble & value) {
  return value ? *value : Float::nan;
}

inline auto g_cast(double value) {
  return value;
}

inline auto g_cast(const Ouint8_t & value) {
  return static_cast< uint64_t2 >(value ? *value : 0);
}

inline auto g_cast(uint8_t value) {
  return static_cast< uint64_t2 >(value);
}

inline auto g_cast(const Ouint32_t & value) {
  return static_cast< uint64_t2 >(value ? *value : 0);
}

inline auto g_cast(uint32_t value) {
  return static_cast< uint64_t2 >(value);
}
