#include "ext_gdal_base.hpp"

extern "C" void init_ext_gdal_base() {
  Module rb_mGDAL = define_module("GDAL");
  Data_Type<GDAL::Base> rb_cGDAL_dc_Base = define_class_under<GDAL::Base>(rb_mGDAL, "Base");
  rb_cGDAL_dc_Base.define_singleton_function("srid", &GDAL::Base::_srid_);
  rb_cGDAL_dc_Base.define_singleton_function("wkt", &GDAL::Base::_wkt_);
  rb_cGDAL_dc_Base.define_singleton_function("proj4", &GDAL::Base::_proj4_);
  rb_cGDAL_dc_Base.define_singleton_function("orientation", &GDAL::Base::_orientation_);
  rb_cGDAL_dc_Base.define_method("srid", &GDAL::Base::srid);
  rb_cGDAL_dc_Base.define_method("wkt", &GDAL::Base::wkt);
  rb_cGDAL_dc_Base.define_method("proj4", &GDAL::Base::proj4);
  rb_cGDAL_dc_Base.define_method("orientation", &GDAL::Base::orientation);
}
