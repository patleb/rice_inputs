#include "ext_net_cdf_dim.hpp"

extern "C" void init_ext_net_cdf_dim() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::Dim> rb_cNetCDF_dc_Dim = define_class_under<NetCDF::Dim, NetCDF::BelongsToFile>(rb_mNetCDF, "Dim");
  rb_cNetCDF_dc_Dim.define_constructor(Constructor<NetCDF::Dim, const NetCDF::Dim&>());
  rb_cNetCDF_dc_Dim.define_method("name", &NetCDF::Dim::name);
  rb_cNetCDF_dc_Dim.define_method("name=", &NetCDF::Dim::rename);
  rb_cNetCDF_dc_Dim.define_method("unlimited?", &NetCDF::Dim::is_unlimited);
  rb_cNetCDF_dc_Dim.define_method("size", &NetCDF::Dim::size);
}
