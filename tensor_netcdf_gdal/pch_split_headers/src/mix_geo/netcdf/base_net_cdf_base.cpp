// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace NetCDF {
    Base::Base(int id):
      id(id) {
    }
    const char * Base::file_format(int file_id) {
      int format;
      check_status( nc_inq_format(file_id, &format), file_id );
      switch (format) {
      case NC_FORMAT_CLASSIC:         return "classic";     // 1
      case NC_FORMAT_64BIT_OFFSET:    return "classic_64";  // 2
      case NC_FORMAT_CDF5:            return "cdf5";        // 5
      case NC_FORMAT_NETCDF4:         return "nc4";         // 3
      case NC_FORMAT_NETCDF4_CLASSIC: return "nc4_classic"; // 4
      default: throw RuntimeError("unknown file format");
      }
    }
    void Base::check_status(int code, int file_id, int id, std::string_view name, const std::stacktrace & trace, const std::source_location & source) {
      switch (code) {
      case NC_NOERR: return;
      case NC_EBADID:
        if (name == "") {
          if (id == NULL_ID)        log_error("NetCDF: Not a valid ID [file_id][", file_id, "]");
          else                      log_error("NetCDF: Not a valid ID [file_id][", file_id, "][id][", id, "]");
        } else if (id == NULL_ID) { log_error("NetCDF: Not a valid ID [file_id][", file_id, "][name][", name, "]");
        } else {                    log_error("NetCDF: Not a valid ID [file_id][", file_id, "][id][", id, "][name][", name, "]");
        } break;
      }
      const char * msg = 0;
      if (NC_ISSYSERR(code)) {
        msg = std::strerror(code);
        msg = msg ? msg : "unknown system error";
      } else {
        msg = nc_strerror(code);
      }
      throw RuntimeError(msg, trace, source);
    }
    void Base::check_classic(int file_id, const std::stacktrace & trace, const std::source_location & source) {
      if (file_format(file_id) != "classic") {
        throw RuntimeError("not a classic file", trace, source);
      }
    }
}
