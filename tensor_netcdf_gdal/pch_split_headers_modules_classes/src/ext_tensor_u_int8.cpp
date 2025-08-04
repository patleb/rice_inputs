#include "ext_tensor_u_int8.hpp"

extern "C" void init_ext_tensor_u_int8() {
  Module rb_mTensor = define_module("Tensor");
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
}
