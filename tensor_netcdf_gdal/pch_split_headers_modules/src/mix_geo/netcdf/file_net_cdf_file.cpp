// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace NetCDF {
    File::File(const string & path, Ostring mode, Obool nc4_classic, Obool classic, Obool share):
      Base() {
      open(path, mode, nc4_classic, classic, share);
    }
    File::~File() {
      try {
        close();
      }
      catch (std::exception & e) {
        log_error(e.what());
      }
    }
    void File::open(const string & path, Ostring mode, Obool nc4_classic, Obool classic, Obool share) {
      if (!is_closed()) throw RuntimeError("file already opened");
      auto _mode_ = mode.value_or("r");
      auto _nc4_classic_ = nc4_classic.value_or(false);
      auto _classic_ = classic.value_or(false);
      auto _share_ = share.value_or(false);
      int flags;
      bool create = false;
      if (_mode_ == "r") {
        flags = NC_NOWRITE;
      } else if (_mode_ == "w") {
        flags = NC_CLOBBER;
        create = true;
      } else if (_mode_ == "a") {
        if (std::filesystem::exists(path)) {
          flags = NC_WRITE;
        } else {
          flags = NC_NOCLOBBER;
          create = true;
        }
      } else {
        throw RuntimeError("mode not supported");
      }
      if (_classic_ && _share_) flags = flags | NC_SHARE;
      if (create) {
        if (!_classic_) flags = flags | NC_NETCDF4;
        if (_nc4_classic_) flags = flags | NC_CLASSIC_MODEL;
        check_status( nc_create(path.c_str(), flags, &this->id) );
      } else {
        check_status( nc_open(path.c_str(), flags, &this->id) );
      }
      this->path = path;
      this->mode = _mode_;
      this->flags = flags;
    }
    void File::close() {
      if (is_closed()) return;
      check_status( nc_close(id) );
      this->id = NULL_ID;
    }
    bool File::is_closed() const {
      return id == NULL_ID;
    }
    void File::sync() const {
      check_status( nc_sync(id) );
    }
    void File::set_define_mode(bool define_mode) {
      if (define_mode) {
        check_status( nc_redef(id) );
      } else {
        check_status( nc_enddef(id) );
      }
    }
    bool File::set_fill(bool fill) {
      int mode, mode_was;
      mode = fill ? NC_FILL : NC_NOFILL;
      check_status( nc_set_fill(id, mode, &mode_was) );
      return mode != mode_was;
    }
    void File::check_status(int code, const std::stacktrace & trace, const std::source_location & source) const {
      Base::check_status(code, id, NULL_ID, "", trace, source);
    }
}
