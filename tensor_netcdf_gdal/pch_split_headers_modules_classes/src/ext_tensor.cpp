#include "ext_tensor.hpp"

extern "C" void init_ext_tensor() {
  Module rb_mTensor = define_module("Tensor");
  Enum<Tensor::Type> rb_eTensor_dc_Type = define_enum_under<Tensor::Type>("Type", rb_mTensor);
  rb_eTensor_dc_Type.define_value("Int32", Tensor::Type::Int32);
  rb_eTensor_dc_Type.define_value("Int64", Tensor::Type::Int64);
  rb_eTensor_dc_Type.define_value("SFloat", Tensor::Type::SFloat);
  rb_eTensor_dc_Type.define_value("DFloat", Tensor::Type::DFloat);
  rb_eTensor_dc_Type.define_value("UInt8", Tensor::Type::UInt8);
  rb_eTensor_dc_Type.define_value("UInt32", Tensor::Type::UInt32);
}
