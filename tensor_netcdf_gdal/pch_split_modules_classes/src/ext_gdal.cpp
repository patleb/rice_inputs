#include "ext_gdal.hpp"

extern "C" void init_ext_gdal() {
  Module rb_mGDAL = define_module("GDAL");
  rb_mGDAL.define_singleton_function("version", &GDAL::version);
}
