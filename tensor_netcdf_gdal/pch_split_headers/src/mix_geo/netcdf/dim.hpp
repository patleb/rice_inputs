#pragma once

namespace NetCDF {
  class Dim : public BelongsToFile {
    public:

    using BelongsToFile::BelongsToFile;

    static vector< Dim > all(int file_id);

    static Dim find(int file_id, const string & name);

    static Dim create(int file_id, const string & name, const Osize_t & size = nil);

    string name() const;

    void rename(const string & new_name) const;

    size_t size() const;

    bool is_unlimited() const;
  };
}
