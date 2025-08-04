#pragma once

#define NO_POINT -1

namespace GDAL {
  class Raster : public Base {
    public:

    struct Transform {
      Vector  mesh;
      size_t  width, height; // always >= to the original grid
      double  x0, y0;
      double  dx, dy;
      ssize_t rx, ry; // always >= 1

      inline auto _mesh_() const { return mesh; }
      inline auto shape()  const { return Vsize_t{ height, width }; }

      string cache_key(const Raster & raster) const;
    };

    Tensor::NType z;
    Tensor::Base & tensor; // stored as [y, x]
    size_t width, height;
    double x0 = Float::nan, y0 = Float::nan;
    double dx = Float::nan, dy = Float::nan;

    Raster(Tensor::Base & z, Tensor::Type type, const Vdouble & x01_y01, const Ostring & proj = nil);

    Raster(const Raster & raster);

    Raster & operator=(const Raster & raster) = delete;

    inline auto fill_value() const { return tensor.nodata_value(); }
    inline auto shape()      const { return tensor.shape; }
    inline auto type()       const { return tensor.type; }

    Vdouble x() const;

    Vdouble y() const;

    inline auto _z_() const { return z; }

    Raster reproject(const string & proj, const GType & fill_value = none, Obool compact = nil, Obool memoize = nil) const;

    Raster::Transform transform_for(const string & proj, Obool compact = nil, Obool memoize = nil) const;
        // NOTE std::floor --> a bigger width would mean a smaller dx_min and rx could become too small

    string cache_key() const;

    private:

    auto cache_key_for(const string & proj, bool compact) const;

    Raster::Transform cached_transform_for(const string & proj, bool compact) const;

    vector< Vssize_t > nearest_for(const Transform & tf, Obool memoize = nil) const;

    vector< Vssize_t > & cached_nearest_for(const Transform & tf) const;
  };
}
