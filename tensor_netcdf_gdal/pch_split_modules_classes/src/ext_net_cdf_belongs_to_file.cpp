#include "ext_net_cdf_belongs_to_file.hpp"

extern "C" void init_ext_net_cdf_belongs_to_file() {
  Module rb_mNetCDF = define_module("NetCDF");
  Data_Type<NetCDF::BelongsToFile> rb_cNetCDF_dc_BelongsToFile = define_class_under<NetCDF::BelongsToFile, NetCDF::Base>(rb_mNetCDF, "BelongsToFile");
  rb_cNetCDF_dc_BelongsToFile.define_attr("file_id", &NetCDF::BelongsToFile::file_id, AttrAccess::Read);
}
