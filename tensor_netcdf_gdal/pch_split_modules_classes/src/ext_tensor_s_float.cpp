#include "ext_tensor_s_float.hpp"

extern "C" void init_ext_tensor_s_float() {
  Module rb_mTensor = define_module("Tensor");
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
}
