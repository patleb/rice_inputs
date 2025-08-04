// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace NetCDF {
    TypeError::TypeError(const std::stacktrace & trace, const std::source_location & source):
      RuntimeError("TypeError", trace, source) {
    }
}
