#pragma once

namespace GDAL {
  class Vector : public Base {
    public:

    Vdouble x;
    Vdouble y;
    size_t size;

    Vector() = default;

    Vector(const Vdouble & x, const Vdouble & y, const Ostring & proj = nil);

    Vector(const Vdouble & x, const Vdouble & y, OGRSpatialReference * srs);

    inline auto _x_() const { return x; }
    inline auto _y_() const { return y; }

    vector< std::pair< double, double >> points() const;

    Vector reproject(const string & dst_proj) const;
  };
}
