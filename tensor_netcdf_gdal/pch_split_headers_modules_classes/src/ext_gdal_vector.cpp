#include "ext_gdal_vector.hpp"

extern "C" void init_ext_gdal_vector() {
  Module rb_mGDAL = define_module("GDAL");
  Data_Type<GDAL::Vector> rb_cGDAL_dc_Vector = define_class_under<GDAL::Vector, GDAL::Base>(rb_mGDAL, "Vector");
  rb_cGDAL_dc_Vector.define_attr("size", &GDAL::Vector::size, AttrAccess::Read);
  rb_cGDAL_dc_Vector.define_constructor(Constructor<GDAL::Vector, const GDAL::Vector&>());
  rb_cGDAL_dc_Vector.define_constructor(Constructor<GDAL::Vector, const Vdouble &, const Vdouble &, const Ostring &>(), Arg("x"), Arg("y"), Arg("proj") = nil);
  rb_cGDAL_dc_Vector.define_method("x", &GDAL::Vector::_x_);
  rb_cGDAL_dc_Vector.define_method("y", &GDAL::Vector::_y_);
  rb_cGDAL_dc_Vector.define_method("points", &GDAL::Vector::points);
  rb_cGDAL_dc_Vector.define_method("reproject", &GDAL::Vector::reproject);
}
