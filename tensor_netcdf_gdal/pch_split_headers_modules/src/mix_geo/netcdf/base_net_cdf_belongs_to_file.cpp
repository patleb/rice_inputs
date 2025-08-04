// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace NetCDF {
    BelongsToFile::BelongsToFile(int file_id, int id):
      Base(id),
      file_id(file_id) {
    }
    void BelongsToFile::check_status(int code, const std::stacktrace & trace, const std::source_location & source) const {
      Base::check_status(code, file_id, id, "", trace, source);
    }
}
