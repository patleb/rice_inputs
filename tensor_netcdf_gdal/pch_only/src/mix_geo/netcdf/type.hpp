#pragma once

namespace NetCDF {
  using std::string;
  using std::vector;

  enum class Type {
    Int32 = NC_INT,
    Int64 = NC_INT64,
    SFloat = NC_FLOAT,
    DFloat = NC_DOUBLE,
    UInt8 = NC_UBYTE,
    UInt32 = NC_UINT,
    String = NC_CHAR
  };

  class TypeError : public RuntimeError {
    public:

    TypeError(CONTEXT(trace, source)):
      RuntimeError("TypeError", trace, source) {
    }
  };

  inline int type_id(const Tensor::NType & values) {
    switch (values.index()) {
    case 0: return NC_INT;
    case 1: return NC_INT64;
    case 2: return NC_FLOAT;
    case 3: return NC_DOUBLE;
    case 4: return NC_UBYTE;
    case 5: return NC_UINT;
    case 6: return NC_CHAR;
    default: throw TypeError();
    }
  }

  inline int type_id(std::string_view name) {
    if (name == "Int32") return NC_INT;
    if (name == "Int64") return NC_INT64;
    if (name == "SFloat") return NC_FLOAT;
    if (name == "DFloat") return NC_DOUBLE;
    if (name == "UInt8") return NC_UBYTE;
    if (name == "UInt32") return NC_UINT;
    if (name == "String") return NC_CHAR;
    throw TypeError();
  }

  inline Type type(int id) {
    switch (id) {
    case NC_INT: return NetCDF::Type::Int32;
    case NC_INT64: return NetCDF::Type::Int64;
    case NC_FLOAT: return NetCDF::Type::SFloat;
    case NC_DOUBLE: return NetCDF::Type::DFloat;
    case NC_UBYTE: return NetCDF::Type::UInt8;
    case NC_UINT: return NetCDF::Type::UInt32;
    case NC_CHAR: return NetCDF::Type::String;
    }
    throw TypeError();
  }
}
