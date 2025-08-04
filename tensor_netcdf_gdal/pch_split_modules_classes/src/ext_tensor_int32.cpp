#include "ext_tensor_int32.hpp"

extern "C" void init_ext_tensor_int32() {
  Module rb_mTensor = define_module("Tensor");
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
}
