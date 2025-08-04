// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"
// after_include
using namespace NetCDF;
using namespace GDAL;
using namespace Rice;

#include "ext_tensor.hpp"
#include "ext_gdal.hpp"
#include "ext_net_cdf.hpp"
#include "ext_tensor_base.hpp"
#include "ext_tensor_int32.hpp"
#include "ext_tensor_int64.hpp"
#include "ext_tensor_s_float.hpp"
#include "ext_tensor_d_float.hpp"
#include "ext_tensor_u_int8.hpp"
#include "ext_tensor_u_int32.hpp"
#include "ext_gdal_base.hpp"
#include "ext_gdal_vector.hpp"
#include "ext_gdal_raster.hpp"
#include "ext_net_cdf_base.hpp"
#include "ext_net_cdf_file.hpp"
#include "ext_net_cdf_belongs_to_file.hpp"
#include "ext_net_cdf_dim.hpp"
#include "ext_net_cdf_att.hpp"
#include "ext_net_cdf_var.hpp"

extern "C" void Init_ext() {
  // before_initialize
  GDALAllRegister();
  // initialize
  Module rb_mC = define_module("C");
  rb_mC.define_constant("DOUBLE_SAFE_INT64", DOUBLE_SAFE_INT64);
  rb_mC.define_constant("FLOAT_SAFE_INT32", FLOAT_SAFE_INT32);
  Data_Type<Bitset> rb_cBitset = define_class<Bitset>("Bitset");
  rb_cBitset.define_constructor(Constructor<Bitset, const Bitset&>());
  rb_cBitset.define_constructor(Constructor<Bitset, size_t>(), Arg("count"));
  rb_cBitset.define_constructor(Constructor<Bitset, const Vbool &>(), Arg("bools"));
  using rb_bitset_operator00_1 = bool (Bitset::*)(size_t i) const;
  rb_cBitset.define_method<rb_bitset_operator00_1>("[]", &Bitset::operator[]);
  rb_cBitset.define_method("[]=", [](Bitset & self, size_t i, bool value) -> bool {
    self[i] = value;
    return value;
  });
  using rb_bitset_front_1 = bool (Bitset::*)() const;
  rb_cBitset.define_method<rb_bitset_front_1>("first", &Bitset::front);
  using rb_bitset_back_1 = bool (Bitset::*)() const;
  rb_cBitset.define_method<rb_bitset_back_1>("last", &Bitset::back);
  rb_cBitset.define_method("size", &Bitset::size);
  rb_cBitset.define_method("to_s", &Bitset::to_s);
  Module rb_mPROJ = define_module("PROJ");
  rb_mPROJ.define_singleton_function("version", &PROJ::version);
  init_ext_tensor();
  init_ext_gdal();
  init_ext_net_cdf();
  init_ext_tensor_base();
  init_ext_tensor_int32();
  init_ext_tensor_int64();
  init_ext_tensor_s_float();
  init_ext_tensor_d_float();
  init_ext_tensor_u_int8();
  init_ext_tensor_u_int32();
  init_ext_gdal_base();
  init_ext_gdal_vector();
  init_ext_gdal_raster();
  init_ext_net_cdf_base();
  init_ext_net_cdf_file();
  init_ext_net_cdf_belongs_to_file();
  init_ext_net_cdf_dim();
  init_ext_net_cdf_att();
  init_ext_net_cdf_var();
  // after_initialize
}
