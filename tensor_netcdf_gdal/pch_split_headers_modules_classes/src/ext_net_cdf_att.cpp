#include "ext_net_cdf_att.hpp"

extern "C" void init_ext_net_cdf_att() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::Att> rb_cNetCDF_dc_Att = define_class_under<NetCDF::Att, NetCDF::BelongsToFile>(rb_mNetCDF, "Att");
  rb_cNetCDF_dc_Att.define_attr("var_id", &NetCDF::Att::var_id, AttrAccess::Read);
  rb_cNetCDF_dc_Att.define_attr("name", &NetCDF::Att::name, AttrAccess::Read);
  rb_cNetCDF_dc_Att.define_constructor(Constructor<NetCDF::Att, const NetCDF::Att&>());
  rb_cNetCDF_dc_Att.define_method("name=", &NetCDF::Att::rename);
  rb_cNetCDF_dc_Att.define_method("type", &NetCDF::Att::type);
  rb_cNetCDF_dc_Att.define_method("size", &NetCDF::Att::size);
  rb_cNetCDF_dc_Att.define_method("read", &NetCDF::Att::read);
  rb_cNetCDF_dc_Att.define_method("destroy", &NetCDF::Att::destroy);
}
