// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace GDAL {
    Base::Base(const string & proj):
      Base(srs_for(proj)) {
    }
    Base::Base(OGRSpatialReference * srs):
      srs(srs) {
    }
    OGRSpatialReference * Base::srs_for(const string & proj) {
      static std::unordered_map< string, OGRSpatialReference * > cache;
      if (cache.contains(proj)) return cache[proj];
      if (cache.size() >= 64) throw RuntimeError("too many SRS in use");
      OGRErr e;
      const char * c_str = proj.c_str();
      auto srs = new OGRSpatialReference;
      int srid = atoi(c_str);
      if (srid) {
        e = srs->importFromEPSG(srid);
      } else if (proj[0] == '+') {
        e = srs->importFromProj4(c_str);
      } else {
        e = srs->importFromWkt(c_str);
      }
      if (e != OGRERR_NONE) {
        delete srs;
        throw RuntimeError("invalid proj");
      }
      srs->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
      cache[proj] = srs;
      return srs;
    }
    int Base::srid_for(OGRSpatialReference * srs) {
      const char * auth = srs->GetAuthorityName(nullptr);
      const char * code = srs->GetAuthorityCode(nullptr);
      if (auth != nullptr && code != nullptr && string(auth) == "EPSG") {
        return atoi(code);
      }
      int number = srs->GetEPSGGeogCS();
      return number > 0 ? number : 0;
    }
    string Base::wkt_for(OGRSpatialReference * srs) {
      char * c_str = nullptr;
      finally ensure([&]{
        CPLFree(c_str);
      });
      if (srs->exportToWkt(&c_str) != OGRERR_NONE) throw RuntimeError("export wkt error");
      string wkt(c_str);
      return wkt;
    }
    string Base::proj4_for(OGRSpatialReference * srs) {
      char * c_str = nullptr;
      finally ensure([&]{
        CPLFree(c_str);
      });
      if (srs->exportToProj4(&c_str) != OGRERR_NONE) throw RuntimeError("export proj4 error");
      string proj4(c_str);
      return proj4;
    }
    Vint Base::axis_mapping_for(OGRSpatialReference * srs) {
      return srs->GetDataAxisToSRSAxisMapping();
    }
    Vdouble Base::orientation_for(OGRSpatialReference * srs) {
      OGRAxisOrientation orientation;
      auto mapping = axis_mapping_for(srs);
      if (mapping.size() != 2) throw RuntimeError("srs mapping.size() != 2");
      Vdouble xy(2);
      for (size_t i = 0; i < 2; ++i) {
        auto axis = mapping[i] - 1;
        srs->GetAxis(nullptr, axis, &orientation);
        switch (orientation) {
        case OAO_North: xy[i] = -1.0; break; // 1
        case OAO_South: xy[i] =  1.0; break; // 2
        case OAO_East:  xy[i] =  1.0; break; // 3
        case OAO_West:  xy[i] = -1.0; break; // 4
        default:
          throw RuntimeError("unsupported axis");
        }
      }
      return xy;
    }
    Vstring Base::orientation_names_for(OGRSpatialReference * srs) {
      OGRAxisOrientation orientation;
      auto mapping = axis_mapping_for(srs);
      Vstring xy(2);
      for (size_t i = 0; i < 2; ++i) {
        auto axis = mapping[i] - 1;
        srs->GetAxis(nullptr, axis, &orientation);
        switch (orientation) {
        case OAO_North: xy[i] = "North"; break;
        case OAO_South: xy[i] = "South"; break;
        case OAO_East:  xy[i] = "East";  break;
        case OAO_West:  xy[i] = "West";  break;
        }
      }
      return xy;
    }
    int Base::mapping_strategy_for(OGRSpatialReference * srs) {
      return srs->GetAxisMappingStrategy();
    }
    string Base::mapping_strategy_name_for(OGRSpatialReference * srs) {
      switch (mapping_strategy_for(srs)) {
      case OAMS_TRADITIONAL_GIS_ORDER: return "TRADITIONAL_GIS_ORDER";
      case OAMS_AUTHORITY_COMPLIANT:   return "AUTHORITY_COMPLIANT";
      case OAMS_CUSTOM:                return "CUSTOM";
      default:
        throw RuntimeError("unsupported mapping strategy");
      }
    }
    void Base::puts_mark() {
      static int marker_i = 0;
      CPLError(CE_Failure, CPLE_AppDefined, "%s", (string("mark ") + std::to_string(marker_i++)).c_str());
    }
}
