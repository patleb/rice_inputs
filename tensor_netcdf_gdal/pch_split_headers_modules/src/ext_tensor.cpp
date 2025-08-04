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
  Data_Type<Tensor::Base> rb_cTensor_dc_Base = define_class_under<Tensor::Base>(rb_mTensor, "Base");
  rb_cTensor_dc_Base.define_attr("size", &Tensor::Base::size, AttrAccess::Read);
  rb_cTensor_dc_Base.define_attr("rank", &Tensor::Base::rank, AttrAccess::Read);
  rb_cTensor_dc_Base.define_attr("type", &Tensor::Base::type, AttrAccess::Read);
  rb_cTensor_dc_Base.define_method("shape", &Tensor::Base::_shape_);
  rb_cTensor_dc_Base.define_method("offsets", &Tensor::Base::_offsets_);
  Data_Type<Tensor::Int32> rb_cTensor_dc_Int32 = define_class_under<Tensor::Int32, Tensor::Base>(rb_mTensor, "Int32");
  rb_cTensor_dc_Int32.define_attr("fill_value", &Tensor::Int32::fill_value);
  rb_cTensor_dc_Int32.define_singleton_function("from_sql", &Tensor::Int32::from_sql);
  rb_cTensor_dc_Int32.define_constructor(Constructor<Tensor::Int32, const Tensor::Int32&>());
  rb_cTensor_dc_Int32.define_constructor(Constructor<Tensor::Int32, const Vsize_t &, const Oint32_t &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_Int32.define_constructor(Constructor<Tensor::Int32, const Vint32_t &, const Vsize_t &, const Oint32_t &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_Int32.define_method("==", &Tensor::Int32::operator==);
  using rb_tensor_int32_operator00_1 = const int32_t & (Tensor::Int32::*)(size_t i) const;
  rb_cTensor_dc_Int32.define_method<rb_tensor_int32_operator00_1>("[]", &Tensor::Int32::operator[]);
  using rb_tensor_int32_operator00_2 = const int32_t & (Tensor::Int32::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_Int32.define_method<rb_tensor_int32_operator00_2>("[]", &Tensor::Int32::operator[]);
  rb_cTensor_dc_Int32.define_method("[]=", [](Tensor::Int32 & self, const Vsize_t & indexes, const int32_t & value) -> const int32_t & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_int32_front_1 = const int32_t & (Tensor::Int32::*)() const;
  rb_cTensor_dc_Int32.define_method<rb_tensor_int32_front_1>("first", &Tensor::Int32::front);
  using rb_tensor_int32_back_1 = const int32_t & (Tensor::Int32::*)() const;
  rb_cTensor_dc_Int32.define_method<rb_tensor_int32_back_1>("last", &Tensor::Int32::back);
  using rb_tensor_int32_slice_1 = Tensor::Int32 (Tensor::Int32::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_Int32.define_method<rb_tensor_int32_slice_1>("slice", &Tensor::Int32::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_Int32.define_method("values", &Tensor::Int32::values);
  rb_cTensor_dc_Int32.define_method("refill_value", [](Tensor::Int32 & self, int32_t fill_value) -> Tensor::Int32 & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_Int32.define_method("reshape", [](Tensor::Int32 & self, const Vsize_t & shape) -> Tensor::Int32 & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_Int32.define_method("seq", [](Tensor::Int32 & self, const Oint32_t & start) -> Tensor::Int32 & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_Int32.define_method("to_sql", &Tensor::Int32::to_sql);
  rb_cTensor_dc_Int32.define_method("to_string", &Tensor::Int32::to_string);
  Data_Type<Tensor::Int64> rb_cTensor_dc_Int64 = define_class_under<Tensor::Int64, Tensor::Base>(rb_mTensor, "Int64");
  rb_cTensor_dc_Int64.define_attr("fill_value", &Tensor::Int64::fill_value);
  rb_cTensor_dc_Int64.define_singleton_function("from_sql", &Tensor::Int64::from_sql);
  rb_cTensor_dc_Int64.define_constructor(Constructor<Tensor::Int64, const Tensor::Int64&>());
  rb_cTensor_dc_Int64.define_constructor(Constructor<Tensor::Int64, const Vsize_t &, const Oint64_t2 &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_Int64.define_constructor(Constructor<Tensor::Int64, const Vint64_t2 &, const Vsize_t &, const Oint64_t2 &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_Int64.define_method("==", &Tensor::Int64::operator==);
  using rb_tensor_int64_operator00_1 = const int64_t2 & (Tensor::Int64::*)(size_t i) const;
  rb_cTensor_dc_Int64.define_method<rb_tensor_int64_operator00_1>("[]", &Tensor::Int64::operator[]);
  using rb_tensor_int64_operator00_2 = const int64_t2 & (Tensor::Int64::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_Int64.define_method<rb_tensor_int64_operator00_2>("[]", &Tensor::Int64::operator[]);
  rb_cTensor_dc_Int64.define_method("[]=", [](Tensor::Int64 & self, const Vsize_t & indexes, const int64_t2 & value) -> const int64_t2 & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_int64_front_1 = const int64_t2 & (Tensor::Int64::*)() const;
  rb_cTensor_dc_Int64.define_method<rb_tensor_int64_front_1>("first", &Tensor::Int64::front);
  using rb_tensor_int64_back_1 = const int64_t2 & (Tensor::Int64::*)() const;
  rb_cTensor_dc_Int64.define_method<rb_tensor_int64_back_1>("last", &Tensor::Int64::back);
  using rb_tensor_int64_slice_1 = Tensor::Int64 (Tensor::Int64::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_Int64.define_method<rb_tensor_int64_slice_1>("slice", &Tensor::Int64::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_Int64.define_method("values", &Tensor::Int64::values);
  rb_cTensor_dc_Int64.define_method("refill_value", [](Tensor::Int64 & self, int64_t2 fill_value) -> Tensor::Int64 & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_Int64.define_method("reshape", [](Tensor::Int64 & self, const Vsize_t & shape) -> Tensor::Int64 & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_Int64.define_method("seq", [](Tensor::Int64 & self, const Oint64_t2 & start) -> Tensor::Int64 & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_Int64.define_method("to_sql", &Tensor::Int64::to_sql);
  rb_cTensor_dc_Int64.define_method("to_string", &Tensor::Int64::to_string);
  Data_Type<Tensor::SFloat> rb_cTensor_dc_SFloat = define_class_under<Tensor::SFloat, Tensor::Base>(rb_mTensor, "SFloat");
  rb_cTensor_dc_SFloat.define_attr("fill_value", &Tensor::SFloat::fill_value);
  rb_cTensor_dc_SFloat.define_singleton_function("from_sql", &Tensor::SFloat::from_sql);
  rb_cTensor_dc_SFloat.define_constructor(Constructor<Tensor::SFloat, const Tensor::SFloat&>());
  rb_cTensor_dc_SFloat.define_constructor(Constructor<Tensor::SFloat, const Vsize_t &, const Ofloat &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_SFloat.define_constructor(Constructor<Tensor::SFloat, const Vfloat &, const Vsize_t &, const Ofloat &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_SFloat.define_method("==", &Tensor::SFloat::operator==);
  using rb_tensor_s_float_operator00_1 = const float & (Tensor::SFloat::*)(size_t i) const;
  rb_cTensor_dc_SFloat.define_method<rb_tensor_s_float_operator00_1>("[]", &Tensor::SFloat::operator[]);
  using rb_tensor_s_float_operator00_2 = const float & (Tensor::SFloat::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_SFloat.define_method<rb_tensor_s_float_operator00_2>("[]", &Tensor::SFloat::operator[]);
  rb_cTensor_dc_SFloat.define_method("[]=", [](Tensor::SFloat & self, const Vsize_t & indexes, const float & value) -> const float & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_s_float_front_1 = const float & (Tensor::SFloat::*)() const;
  rb_cTensor_dc_SFloat.define_method<rb_tensor_s_float_front_1>("first", &Tensor::SFloat::front);
  using rb_tensor_s_float_back_1 = const float & (Tensor::SFloat::*)() const;
  rb_cTensor_dc_SFloat.define_method<rb_tensor_s_float_back_1>("last", &Tensor::SFloat::back);
  using rb_tensor_s_float_slice_1 = Tensor::SFloat (Tensor::SFloat::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_SFloat.define_method<rb_tensor_s_float_slice_1>("slice", &Tensor::SFloat::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_SFloat.define_method("values", &Tensor::SFloat::values);
  rb_cTensor_dc_SFloat.define_method("refill_value", [](Tensor::SFloat & self, float fill_value) -> Tensor::SFloat & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_SFloat.define_method("reshape", [](Tensor::SFloat & self, const Vsize_t & shape) -> Tensor::SFloat & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_SFloat.define_method("seq", [](Tensor::SFloat & self, const Ofloat & start) -> Tensor::SFloat & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_SFloat.define_method("to_sql", &Tensor::SFloat::to_sql);
  rb_cTensor_dc_SFloat.define_method("to_string", &Tensor::SFloat::to_string);
  Data_Type<Tensor::DFloat> rb_cTensor_dc_DFloat = define_class_under<Tensor::DFloat, Tensor::Base>(rb_mTensor, "DFloat");
  rb_cTensor_dc_DFloat.define_attr("fill_value", &Tensor::DFloat::fill_value);
  rb_cTensor_dc_DFloat.define_singleton_function("from_sql", &Tensor::DFloat::from_sql);
  rb_cTensor_dc_DFloat.define_constructor(Constructor<Tensor::DFloat, const Tensor::DFloat&>());
  rb_cTensor_dc_DFloat.define_constructor(Constructor<Tensor::DFloat, const Vsize_t &, const Odouble &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_DFloat.define_constructor(Constructor<Tensor::DFloat, const Vdouble &, const Vsize_t &, const Odouble &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_DFloat.define_method("==", &Tensor::DFloat::operator==);
  using rb_tensor_d_float_operator00_1 = const double & (Tensor::DFloat::*)(size_t i) const;
  rb_cTensor_dc_DFloat.define_method<rb_tensor_d_float_operator00_1>("[]", &Tensor::DFloat::operator[]);
  using rb_tensor_d_float_operator00_2 = const double & (Tensor::DFloat::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_DFloat.define_method<rb_tensor_d_float_operator00_2>("[]", &Tensor::DFloat::operator[]);
  rb_cTensor_dc_DFloat.define_method("[]=", [](Tensor::DFloat & self, const Vsize_t & indexes, const double & value) -> const double & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_d_float_front_1 = const double & (Tensor::DFloat::*)() const;
  rb_cTensor_dc_DFloat.define_method<rb_tensor_d_float_front_1>("first", &Tensor::DFloat::front);
  using rb_tensor_d_float_back_1 = const double & (Tensor::DFloat::*)() const;
  rb_cTensor_dc_DFloat.define_method<rb_tensor_d_float_back_1>("last", &Tensor::DFloat::back);
  using rb_tensor_d_float_slice_1 = Tensor::DFloat (Tensor::DFloat::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_DFloat.define_method<rb_tensor_d_float_slice_1>("slice", &Tensor::DFloat::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_DFloat.define_method("values", &Tensor::DFloat::values);
  rb_cTensor_dc_DFloat.define_method("refill_value", [](Tensor::DFloat & self, double fill_value) -> Tensor::DFloat & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_DFloat.define_method("reshape", [](Tensor::DFloat & self, const Vsize_t & shape) -> Tensor::DFloat & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_DFloat.define_method("seq", [](Tensor::DFloat & self, const Odouble & start) -> Tensor::DFloat & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_DFloat.define_method("to_sql", &Tensor::DFloat::to_sql);
  rb_cTensor_dc_DFloat.define_method("to_string", &Tensor::DFloat::to_string);
  Data_Type<Tensor::UInt8> rb_cTensor_dc_UInt8 = define_class_under<Tensor::UInt8, Tensor::Base>(rb_mTensor, "UInt8");
  rb_cTensor_dc_UInt8.define_attr("fill_value", &Tensor::UInt8::fill_value);
  rb_cTensor_dc_UInt8.define_singleton_function("from_sql", &Tensor::UInt8::from_sql);
  rb_cTensor_dc_UInt8.define_constructor(Constructor<Tensor::UInt8, const Tensor::UInt8&>());
  rb_cTensor_dc_UInt8.define_constructor(Constructor<Tensor::UInt8, const Vsize_t &, const Ouint8_t &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_UInt8.define_constructor(Constructor<Tensor::UInt8, const Vuint8_t &, const Vsize_t &, const Ouint8_t &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_UInt8.define_method("==", &Tensor::UInt8::operator==);
  using rb_tensor_u_int8_operator00_1 = const uint8_t & (Tensor::UInt8::*)(size_t i) const;
  rb_cTensor_dc_UInt8.define_method<rb_tensor_u_int8_operator00_1>("[]", &Tensor::UInt8::operator[]);
  using rb_tensor_u_int8_operator00_2 = const uint8_t & (Tensor::UInt8::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_UInt8.define_method<rb_tensor_u_int8_operator00_2>("[]", &Tensor::UInt8::operator[]);
  rb_cTensor_dc_UInt8.define_method("[]=", [](Tensor::UInt8 & self, const Vsize_t & indexes, const uint8_t & value) -> const uint8_t & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_u_int8_front_1 = const uint8_t & (Tensor::UInt8::*)() const;
  rb_cTensor_dc_UInt8.define_method<rb_tensor_u_int8_front_1>("first", &Tensor::UInt8::front);
  using rb_tensor_u_int8_back_1 = const uint8_t & (Tensor::UInt8::*)() const;
  rb_cTensor_dc_UInt8.define_method<rb_tensor_u_int8_back_1>("last", &Tensor::UInt8::back);
  using rb_tensor_u_int8_slice_1 = Tensor::UInt8 (Tensor::UInt8::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_UInt8.define_method<rb_tensor_u_int8_slice_1>("slice", &Tensor::UInt8::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_UInt8.define_method("values", &Tensor::UInt8::values);
  rb_cTensor_dc_UInt8.define_method("refill_value", [](Tensor::UInt8 & self, uint8_t fill_value) -> Tensor::UInt8 & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_UInt8.define_method("reshape", [](Tensor::UInt8 & self, const Vsize_t & shape) -> Tensor::UInt8 & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_UInt8.define_method("seq", [](Tensor::UInt8 & self, const Ouint8_t & start) -> Tensor::UInt8 & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_UInt8.define_method("to_sql", &Tensor::UInt8::to_sql);
  rb_cTensor_dc_UInt8.define_method("to_string", &Tensor::UInt8::to_string);
  Data_Type<Tensor::UInt32> rb_cTensor_dc_UInt32 = define_class_under<Tensor::UInt32, Tensor::Base>(rb_mTensor, "UInt32");
  rb_cTensor_dc_UInt32.define_attr("fill_value", &Tensor::UInt32::fill_value);
  rb_cTensor_dc_UInt32.define_singleton_function("from_sql", &Tensor::UInt32::from_sql);
  rb_cTensor_dc_UInt32.define_constructor(Constructor<Tensor::UInt32, const Tensor::UInt32&>());
  rb_cTensor_dc_UInt32.define_constructor(Constructor<Tensor::UInt32, const Vsize_t &, const Ouint32_t &>(), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_UInt32.define_constructor(Constructor<Tensor::UInt32, const Vuint32_t &, const Vsize_t &, const Ouint32_t &>(), Arg("values"), Arg("shape"), Arg("fill_value") = nil);
  rb_cTensor_dc_UInt32.define_method("==", &Tensor::UInt32::operator==);
  using rb_tensor_u_int32_operator00_1 = const uint32_t & (Tensor::UInt32::*)(size_t i) const;
  rb_cTensor_dc_UInt32.define_method<rb_tensor_u_int32_operator00_1>("[]", &Tensor::UInt32::operator[]);
  using rb_tensor_u_int32_operator00_2 = const uint32_t & (Tensor::UInt32::*)(const Vsize_t & indexes) const;
  rb_cTensor_dc_UInt32.define_method<rb_tensor_u_int32_operator00_2>("[]", &Tensor::UInt32::operator[]);
  rb_cTensor_dc_UInt32.define_method("[]=", [](Tensor::UInt32 & self, const Vsize_t & indexes, const uint32_t & value) -> const uint32_t & {
    self[indexes] = value;
    return value;
  });
  using rb_tensor_u_int32_front_1 = const uint32_t & (Tensor::UInt32::*)() const;
  rb_cTensor_dc_UInt32.define_method<rb_tensor_u_int32_front_1>("first", &Tensor::UInt32::front);
  using rb_tensor_u_int32_back_1 = const uint32_t & (Tensor::UInt32::*)() const;
  rb_cTensor_dc_UInt32.define_method<rb_tensor_u_int32_back_1>("last", &Tensor::UInt32::back);
  using rb_tensor_u_int32_slice_1 = Tensor::UInt32 (Tensor::UInt32::*)(const Vsize_t &, const Vsize_t &, const Vsize_t &) const;
  rb_cTensor_dc_UInt32.define_method<rb_tensor_u_int32_slice_1>("slice", &Tensor::UInt32::slice, Arg("start") = Vsize_t(), Arg("count") = Vsize_t(), Arg("stride") = Vsize_t());
  rb_cTensor_dc_UInt32.define_method("values", &Tensor::UInt32::values);
  rb_cTensor_dc_UInt32.define_method("refill_value", [](Tensor::UInt32 & self, uint32_t fill_value) -> Tensor::UInt32 & {
    self.refill_value(fill_value);
    return self;
  });
  rb_cTensor_dc_UInt32.define_method("reshape", [](Tensor::UInt32 & self, const Vsize_t & shape) -> Tensor::UInt32 & {
    self.reshape(shape);
    return self;
  });
  rb_cTensor_dc_UInt32.define_method("seq", [](Tensor::UInt32 & self, const Ouint32_t & start) -> Tensor::UInt32 & {
    self.seq(start);
    return self;
  });
  rb_cTensor_dc_UInt32.define_method("to_sql", &Tensor::UInt32::to_sql);
  rb_cTensor_dc_UInt32.define_method("to_string", &Tensor::UInt32::to_string);
}
