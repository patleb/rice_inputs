#pragma once

namespace GDAL {
  using std::string;
  using std::vector;

  class Base {
    public:

    OGRSpatialReference * srs = nullptr;

    Base() = default;

    explicit Base(const string & proj);

    inline static auto _srid_(const string & proj)                  { return atoi(proj.c_str()); }
    inline static auto _wkt_(const string & proj)                   { return wkt_for(srs_for(proj)); }
    inline static auto _proj4_(const string & proj)                 { return proj4_for(srs_for(proj)); }
    inline static auto _axis_mapping_(const string & proj)          { return axis_mapping_for(srs_for(proj)); }
    inline static auto _orientation_(const string & proj)           { return orientation_for(srs_for(proj)); }
    inline static auto _orientation_names_(const string & proj)     { return orientation_names_for(srs_for(proj)); }
    inline static auto _mapping_strategy_(const string & proj)      { return mapping_strategy_for(srs_for(proj)); }
    inline static auto _mapping_strategy_name_(const string & proj) { return mapping_strategy_for(srs_for(proj)); }

    inline auto srid()                  const { return srid_for(srs); }
    inline auto wkt()                   const { return wkt_for(srs); }
    inline auto proj4()                 const { return proj4_for(srs); }
    inline auto axis_mapping()          const { return axis_mapping_for(srs); }
    inline auto orientation()           const { return orientation_for(srs); }
    inline auto orientation_names()     const { return orientation_names_for(srs); }
    inline auto mapping_strategy()      const { return mapping_strategy_for(srs); }
    inline auto mapping_strategy_name() const { return mapping_strategy_name_for(srs); }

    protected:

    explicit Base(OGRSpatialReference * srs);

    // NOTE gdal/port/cpl_mem_cache.h --> maxSize = 64
    static OGRSpatialReference * srs_for(const string & proj);

    static int srid_for(OGRSpatialReference * srs);

    static string wkt_for(OGRSpatialReference * srs);

    static string proj4_for(OGRSpatialReference * srs);

    static Vint axis_mapping_for(OGRSpatialReference * srs);

    static Vdouble orientation_for(OGRSpatialReference * srs);
          // OAO_Other = 0
          // OAO_Up    = 5 --> Up (to space)
          // OAO_Down  = 6 --> Down (to Earth center)

    static Vstring orientation_names_for(OGRSpatialReference * srs);

    static int mapping_strategy_for(OGRSpatialReference * srs);

    static string mapping_strategy_name_for(OGRSpatialReference * srs);

    static void puts_mark();
  };
}
