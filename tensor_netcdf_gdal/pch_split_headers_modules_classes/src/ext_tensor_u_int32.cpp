#include "ext_tensor_u_int32.hpp"

extern "C" void init_ext_tensor_u_int32() {
  Module rb_mTensor = define_module("Tensor");
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
