#include "ext_net_cdf.hpp"

extern "C" void init_ext_net_cdf() {
  Module rb_mNetCDF = define_module("NetCDF");
  rb_mNetCDF.define_constant("NULL_ID", NULL_ID);
  rb_mNetCDF.define_constant("GLOBAL", NC_GLOBAL);
  rb_mNetCDF.define_constant("NOWRITE", NC_NOWRITE);
  rb_mNetCDF.define_constant("WRITE", NC_WRITE);
  rb_mNetCDF.define_constant("CLOBBER", NC_CLOBBER);
  rb_mNetCDF.define_constant("NOCLOBBER", NC_NOCLOBBER);
  rb_mNetCDF.define_constant("CLASSIC_MODEL", NC_CLASSIC_MODEL);
  rb_mNetCDF.define_constant("SHARE", NC_SHARE);
  rb_mNetCDF.define_constant("NETCDF4", NC_NETCDF4);
  rb_mNetCDF.define_constant("UNLIMITED", NC_UNLIMITED);
  rb_mNetCDF.define_constant("FILL_STRING", NC_FILL_CHAR);
  rb_mNetCDF.define_constant("FILL_INT8", NC_FILL_BYTE);
  rb_mNetCDF.define_constant("FILL_INT16", NC_FILL_SHORT);
  rb_mNetCDF.define_constant("FILL_INT32", NC_FILL_INT);
  rb_mNetCDF.define_constant("FILL_INT64", NC_FILL_INT64);
  rb_mNetCDF.define_constant("FILL_SFLOAT", NC_FILL_FLOAT);
  rb_mNetCDF.define_constant("FILL_DFLOAT", NC_FILL_DOUBLE);
  rb_mNetCDF.define_constant("FILL_UINT8", NC_FILL_UBYTE);
  rb_mNetCDF.define_constant("FILL_UINT16", NC_FILL_USHORT);
  rb_mNetCDF.define_constant("FILL_UINT32", NC_FILL_UINT);
  rb_mNetCDF.define_constant("FILL_UINT64", NC_FILL_UINT64);
  Enum<NetCDF::Type> rb_eNetCDF_dc_Type = define_enum_under<NetCDF::Type>("Type", rb_mNetCDF);
  rb_eNetCDF_dc_Type.define_value("Int32", NetCDF::Type::Int32);
  rb_eNetCDF_dc_Type.define_value("Int64", NetCDF::Type::Int64);
  rb_eNetCDF_dc_Type.define_value("SFloat", NetCDF::Type::SFloat);
  rb_eNetCDF_dc_Type.define_value("DFloat", NetCDF::Type::DFloat);
  rb_eNetCDF_dc_Type.define_value("UInt8", NetCDF::Type::UInt8);
  rb_eNetCDF_dc_Type.define_value("UInt32", NetCDF::Type::UInt32);
  rb_eNetCDF_dc_Type.define_value("String", NetCDF::Type::String);
  rb_mNetCDF.define_singleton_function("version", &NetCDF::version);
}
