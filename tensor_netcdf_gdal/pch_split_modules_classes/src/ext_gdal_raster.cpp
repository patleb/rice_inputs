#include "ext_gdal_raster.hpp"

extern "C" void init_ext_gdal_raster() {
  Module rb_mGDAL = define_module("GDAL");
  Data_Type<GDAL::Raster> rb_cGDAL_dc_Raster = define_class_under<GDAL::Raster, GDAL::Base>(rb_mGDAL, "Raster");
  Data_Type<GDAL::Raster::Transform> rb_cGDAL_dc_Raster_dc_Transform = define_class_under<GDAL::Raster::Transform>(rb_cGDAL_dc_Raster, "Transform");
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("width", &GDAL::Raster::Transform::width, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("height", &GDAL::Raster::Transform::height, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("x0", &GDAL::Raster::Transform::x0, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("y0", &GDAL::Raster::Transform::y0, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("dx", &GDAL::Raster::Transform::dx, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("dy", &GDAL::Raster::Transform::dy, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("rx", &GDAL::Raster::Transform::rx, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_attr("ry", &GDAL::Raster::Transform::ry, AttrAccess::Read);
  rb_cGDAL_dc_Raster_dc_Transform.define_method("mesh", &GDAL::Raster::Transform::_mesh_);
  rb_cGDAL_dc_Raster_dc_Transform.define_method("shape", &GDAL::Raster::Transform::shape);
  rb_cGDAL_dc_Raster_dc_Transform.define_method("cache_key", &GDAL::Raster::Transform::cache_key);
  rb_cGDAL_dc_Raster.define_attr("width", &GDAL::Raster::width, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_attr("height", &GDAL::Raster::height, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_attr("x0", &GDAL::Raster::x0, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_attr("y0", &GDAL::Raster::y0, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_attr("dx", &GDAL::Raster::dx, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_attr("dy", &GDAL::Raster::dy, AttrAccess::Read);
  rb_cGDAL_dc_Raster.define_constructor(Constructor<GDAL::Raster, const GDAL::Raster&>());
  rb_cGDAL_dc_Raster.define_constructor(Constructor<GDAL::Raster, Tensor::Base &, Tensor::Type, const Vdouble &, const Ostring &>(), Arg("z"), Arg("type"), Arg("x01_y01"), Arg("proj") = nil);
  rb_cGDAL_dc_Raster.define_method("fill_value", &GDAL::Raster::fill_value);
  rb_cGDAL_dc_Raster.define_method("shape", &GDAL::Raster::shape);
  rb_cGDAL_dc_Raster.define_method("type", &GDAL::Raster::type);
  rb_cGDAL_dc_Raster.define_method("x", &GDAL::Raster::x);
  rb_cGDAL_dc_Raster.define_method("y", &GDAL::Raster::y);
  rb_cGDAL_dc_Raster.define_method("z", &GDAL::Raster::_z_);
  rb_cGDAL_dc_Raster.define_method("reproject", &GDAL::Raster::reproject);
  rb_cGDAL_dc_Raster.define_method("transform_for", &GDAL::Raster::transform_for);
}
