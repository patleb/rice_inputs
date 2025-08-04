#pragma once

namespace NetCDF {
  class Att : public BelongsToFile {
    public:

    int var_id = NULL_ID;
    string name;

    using BelongsToFile::BelongsToFile;

    Att(int file_id, int var_id, std::string_view name);

    static void copy(int file_id, int var_id, const string & name, int dst_file_id, int dst_var_id = NC_GLOBAL);

    static vector< Att > all(int file_id, int var_id);

    static Att find(int file_id, int var_id, const string & name);

    static Att write(int file_id, int var_id, const string & name, int type_id, const Tensor::Base & values, bool scalar = false);

    static Att write_s(int file_id, int var_id, const string & name, const string & text, bool scalar = false);

    void rename(const string & new_name);

    Type type() const;

    size_t size() const;

    Tensor::NType read() const;

    void destroy() const;

    protected:

    void check_status(int code, CONTEXT(trace, source)) const;

    private:

    int type_id() const;
  };
}
