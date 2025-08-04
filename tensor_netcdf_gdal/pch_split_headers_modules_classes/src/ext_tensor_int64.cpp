#include "ext_tensor_int64.hpp"

extern "C" void init_ext_tensor_int64() {
  Module rb_mTensor = define_module("Tensor");
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
}
