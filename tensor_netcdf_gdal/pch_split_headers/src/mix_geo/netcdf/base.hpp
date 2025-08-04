#pragma once

#define NULL_ID -1

namespace NetCDF {
  class Base {
    public:

    int id = NULL_ID;

    Base() = default;

    explicit Base(int id);

    protected:

    static const char * file_format(int file_id);

    static void check_status(int code, int file_id = NULL_ID, int id = NULL_ID, std::string_view name = "", CONTEXT(trace, source));

    // BUG: https://github.com/Unidata/netcdf-c/issues/597
    static void check_classic(int file_id, CONTEXT(trace, source));
  };

  class BelongsToFile : public Base {
    public:

    int file_id = NULL_ID;

    using Base::Base;

    BelongsToFile(int file_id, int id);

    protected:

    void check_status(int code, CONTEXT(trace, source)) const;
  };
}
