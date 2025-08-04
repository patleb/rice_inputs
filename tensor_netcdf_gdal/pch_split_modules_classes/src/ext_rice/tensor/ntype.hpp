#pragma once

namespace Tensor {
  using NType = std::variant< Int32, Int64, SFloat, DFloat, UInt8, UInt32, Vstring >;

  inline Tensor::NType build(Tensor::Type type, const Vsize_t & shape, const GType & fill_value = none) {
    switch (type) {
    case Tensor::Type::Int32: return Tensor::Int32(shape, g_cast< int32_t >(fill_value));
    case Tensor::Type::Int64: return Tensor::Int64(shape, g_cast< int64_t2 >(fill_value));
    case Tensor::Type::SFloat: return Tensor::SFloat(shape, g_cast< float >(fill_value));
    case Tensor::Type::DFloat: return Tensor::DFloat(shape, g_cast< double >(fill_value));
    case Tensor::Type::UInt8: return Tensor::UInt8(shape, g_cast< uint8_t >(fill_value));
    case Tensor::Type::UInt32: return Tensor::UInt32(shape, g_cast< uint32_t >(fill_value));
    default:
      throw RuntimeError("invalid Tensor::Type");
    }
  }

  inline Tensor::NType cast(Tensor::Base & tensor, Tensor::Type type) {
    switch (type) {
    case Tensor::Type::Int32: return dynamic_cast< Tensor::Int32 & >(tensor);
    case Tensor::Type::Int64: return dynamic_cast< Tensor::Int64 & >(tensor);
    case Tensor::Type::SFloat: return dynamic_cast< Tensor::SFloat & >(tensor);
    case Tensor::Type::DFloat: return dynamic_cast< Tensor::DFloat & >(tensor);
    case Tensor::Type::UInt8: return dynamic_cast< Tensor::UInt8 & >(tensor);
    case Tensor::Type::UInt32: return dynamic_cast< Tensor::UInt32 & >(tensor);
    default:
      throw RuntimeError("invalid Tensor::Type");
    }
  }

  inline Tensor::Base & cast(Tensor::NType & tensor) {
    switch (tensor.index()) {
    case 0: return std::get< 0 >(tensor);
    case 1: return std::get< 1 >(tensor);
    case 2: return std::get< 2 >(tensor);
    case 3: return std::get< 3 >(tensor);
    case 4: return std::get< 4 >(tensor);
    case 5: return std::get< 5 >(tensor);
    default:
      throw RuntimeError("invalid Tensor::NType");
    }
  }

  inline Tensor::Type type(const Tensor::NType & tensor) {
    switch (tensor.index()) {
    case 0: return Tensor::Type::Int32;
    case 1: return Tensor::Type::Int64;
    case 2: return Tensor::Type::SFloat;
    case 3: return Tensor::Type::DFloat;
    case 4: return Tensor::Type::UInt8;
    case 5: return Tensor::Type::UInt32;
    default:
      throw RuntimeError("invalid Tensor::NType");
    }
  }
}
