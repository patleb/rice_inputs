#include "ext_tensor_base.hpp"

extern "C" void init_ext_tensor_base() {
  Module rb_mTensor = define_module("Tensor");
  Data_Type<Tensor::Base> rb_cTensor_dc_Base = define_class_under<Tensor::Base>(rb_mTensor, "Base");
  rb_cTensor_dc_Base.define_attr("size", &Tensor::Base::size, AttrAccess::Read);
  rb_cTensor_dc_Base.define_attr("rank", &Tensor::Base::rank, AttrAccess::Read);
  rb_cTensor_dc_Base.define_attr("type", &Tensor::Base::type, AttrAccess::Read);
  rb_cTensor_dc_Base.define_method("shape", &Tensor::Base::_shape_);
  rb_cTensor_dc_Base.define_method("offsets", &Tensor::Base::_offsets_);
}
