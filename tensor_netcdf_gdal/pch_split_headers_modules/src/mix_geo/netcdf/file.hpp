#pragma once

namespace NetCDF {
  class File : public Base {
    public:

    string path;
    string mode;
    int flags;

    using Base::Base;

    explicit File(const string & path, Ostring mode = nil, Obool nc4_classic = nil, Obool classic = nil, Obool share = nil);
    File(const File &) = delete;
    File(File &&) = delete;
    File & operator=(const File &) = delete;
    File & operator=(File &&) = delete;

    ~File();

    void open(const string & path, Ostring mode = nil, Obool nc4_classic = nil, Obool classic = nil, Obool share = nil);

    void close();

    bool is_closed() const;

    void sync() const;

    void set_define_mode(bool define_mode);

    bool set_fill(bool fill);

    inline auto format() const { return Base::file_format(id); }
    inline auto dims()   const { return Dim::all(id); }
    inline auto vars()   const { return Var::all(id); }
    inline auto atts()   const { return Att::all(id, NC_GLOBAL); }
    inline auto dim(const string & name) const { return Dim::find(id, name); }
    inline auto var(const string & name) const { return Var::find(id, name); }
    inline auto att(const string & name) const { return Att::find(id, NC_GLOBAL, name); }

    inline auto create_dim(const string & name, const Osize_t & size = nil) const {
      return Dim::create(id, name, size);
    }

    inline auto create_var(const string & name, std::string_view type_name, const vector< Dim > & dims) const {
      return Var::create(id, name, type_name, dims);
    }

    inline auto write_att(const string & name, std::string_view type_name, const Tensor::Base & values) const {
      return Att::write(id, NC_GLOBAL, name, NetCDF::type_id(type_name), values);
    }

    inline auto write_att_s(const string & name, const string & text) const {
      return Att::write_s(id, NC_GLOBAL, name, text);
    }

    protected:

    void check_status(int code, CONTEXT(trace, source)) const;
  };
}
