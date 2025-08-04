#include "ext_net_cdf_file.hpp"

extern "C" void init_ext_net_cdf_file() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::File> rb_cNetCDF_dc_File = define_class_under<NetCDF::File, NetCDF::Base>(rb_mNetCDF, "File");
  rb_cNetCDF_dc_File.define_attr("path", &NetCDF::File::path, AttrAccess::Read);
  rb_cNetCDF_dc_File.define_attr("mode", &NetCDF::File::mode, AttrAccess::Read);
  rb_cNetCDF_dc_File.define_attr("flags", &NetCDF::File::flags, AttrAccess::Read);
  rb_cNetCDF_dc_File.define_constructor(Constructor<NetCDF::File>());
  rb_cNetCDF_dc_File.define_constructor(Constructor<NetCDF::File, const string &, Ostring, Obool, Obool, Obool>(), Arg("path"), Arg("mode") = nil, Arg("nc4_classic") = nil, Arg("classic") = nil, Arg("share") = nil);
  rb_cNetCDF_dc_File.define_method("open", &NetCDF::File::open);
  rb_cNetCDF_dc_File.define_method("close", &NetCDF::File::close);
  rb_cNetCDF_dc_File.define_method("closed?", &NetCDF::File::is_closed);
  rb_cNetCDF_dc_File.define_method("sync", &NetCDF::File::sync);
  rb_cNetCDF_dc_File.define_method("format", &NetCDF::File::format);
  rb_cNetCDF_dc_File.define_method("dims", &NetCDF::File::dims);
  rb_cNetCDF_dc_File.define_method("vars", &NetCDF::File::vars);
  rb_cNetCDF_dc_File.define_method("atts", &NetCDF::File::atts);
  rb_cNetCDF_dc_File.define_method("dim", &NetCDF::File::dim);
  rb_cNetCDF_dc_File.define_method("var", &NetCDF::File::var);
  rb_cNetCDF_dc_File.define_method("att", &NetCDF::File::att);
  rb_cNetCDF_dc_File.define_method("create_dim", &NetCDF::File::create_dim);
  rb_cNetCDF_dc_File.define_method("create_var", &NetCDF::File::create_var);
  rb_cNetCDF_dc_File.define_method("write_att", &NetCDF::File::write_att);
  rb_cNetCDF_dc_File.define_method("write_att_s", &NetCDF::File::write_att_s);
  rb_cNetCDF_dc_File.define_method("set_define_mode", &NetCDF::File::set_define_mode);
  rb_cNetCDF_dc_File.define_method("set_fill", &NetCDF::File::set_fill);
}
