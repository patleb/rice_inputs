#include "ext_net_cdf_var.hpp"

extern "C" void init_ext_net_cdf_var() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::Var> rb_cNetCDF_dc_Var = define_class_under<NetCDF::Var, NetCDF::BelongsToFile>(rb_mNetCDF, "Var");
  rb_cNetCDF_dc_Var.define_constructor(Constructor<NetCDF::Var, const NetCDF::Var&>());
  rb_cNetCDF_dc_Var.define_method("name", &NetCDF::Var::name);
  rb_cNetCDF_dc_Var.define_method("name=", &NetCDF::Var::rename);
  rb_cNetCDF_dc_Var.define_method("type", &NetCDF::Var::type);
  rb_cNetCDF_dc_Var.define_method("dims_count", &NetCDF::Var::dims_count);
  rb_cNetCDF_dc_Var.define_method("dims", &NetCDF::Var::dims);
  rb_cNetCDF_dc_Var.define_method("atts", &NetCDF::Var::atts);
  rb_cNetCDF_dc_Var.define_method("dim", &NetCDF::Var::dim);
  rb_cNetCDF_dc_Var.define_method("att", &NetCDF::Var::att);
  rb_cNetCDF_dc_Var.define_method("shape", &NetCDF::Var::shape);
  rb_cNetCDF_dc_Var.define_method("write_att", &NetCDF::Var::write_att);
  rb_cNetCDF_dc_Var.define_method("write_att_s", &NetCDF::Var::write_att_s);
  rb_cNetCDF_dc_Var.define_method("write", &NetCDF::Var::write);
  rb_cNetCDF_dc_Var.define_method("write_s", &NetCDF::Var::write_s);
  rb_cNetCDF_dc_Var.define_method("read", &NetCDF::Var::read);
  rb_cNetCDF_dc_Var.define_method("fill_value", &NetCDF::Var::fill_value);
  rb_cNetCDF_dc_Var.define_method("set_fill_value", &NetCDF::Var::set_fill_value);
  rb_cNetCDF_dc_Var.define_method("fill", &NetCDF::Var::fill);
  rb_cNetCDF_dc_Var.define_method("set_fill", &NetCDF::Var::set_fill);
  rb_cNetCDF_dc_Var.define_method("endian", &NetCDF::Var::endian);
  rb_cNetCDF_dc_Var.define_method("set_endian", &NetCDF::Var::set_endian);
  rb_cNetCDF_dc_Var.define_method("checksum", &NetCDF::Var::checksum);
  rb_cNetCDF_dc_Var.define_method("set_checksum", &NetCDF::Var::set_checksum);
  rb_cNetCDF_dc_Var.define_method("deflate", &NetCDF::Var::deflate);
  rb_cNetCDF_dc_Var.define_method("set_deflate", &NetCDF::Var::set_deflate);
  rb_cNetCDF_dc_Var.define_method("quantize", &NetCDF::Var::quantize);
  rb_cNetCDF_dc_Var.define_method("set_quantize", &NetCDF::Var::set_quantize);
  rb_cNetCDF_dc_Var.define_method("chunking", &NetCDF::Var::chunking);
  rb_cNetCDF_dc_Var.define_method("set_chunking", &NetCDF::Var::set_chunking);
  rb_cNetCDF_dc_Var.define_method("chunk_cache", &NetCDF::Var::chunk_cache);
  rb_cNetCDF_dc_Var.define_method("set_chunk_cache", &NetCDF::Var::set_chunk_cache);
}
