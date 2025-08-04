#include "ext_net_cdf_base.hpp"

extern "C" void init_ext_net_cdf_base() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::Base> rb_cNetCDF_dc_Base = define_class_under<NetCDF::Base>(rb_mNetCDF, "Base");
  rb_cNetCDF_dc_Base.define_attr("id", &NetCDF::Base::id, AttrAccess::Read);
}
