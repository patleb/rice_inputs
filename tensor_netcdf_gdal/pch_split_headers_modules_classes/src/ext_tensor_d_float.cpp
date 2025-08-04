#include "ext_tensor_d_float.hpp"

extern "C" void init_ext_tensor_d_float() {
  Module rb_mTensor = define_module("Tensor");
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
}
