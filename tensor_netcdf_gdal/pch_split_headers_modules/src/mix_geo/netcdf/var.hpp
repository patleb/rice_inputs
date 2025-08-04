#pragma once

namespace NetCDF {
  class Var : public BelongsToFile {
    public:

    using BelongsToFile::BelongsToFile;

    static vector< Var > all(int file_id);

    static Var find(int file_id, const string & name);

    static Var create(int file_id, const string & name, std::string_view type_name, const vector< Dim > & dims);

    string name() const;

    void rename(string new_name) const;

    Type type() const;

    int dims_count() const;

    vector< Dim > dims() const;

    inline auto atts() const {
      return Att::all(file_id, id);
    }

    Dim dim(const string & name) const;

    inline auto att(const string & name) const {
      return Att::find(file_id, id, name);
    }

    Vsize_t shape() const;

    inline auto write_att(const string & name, std::string_view type_name, const Tensor::Base & values) const {
      return Att::write(file_id, id, name, NetCDF::type_id(type_name), values);
    }

    inline auto write_att_s(const string & name, const string & text) const {
      return Att::write_s(file_id, id, name, text);
    }

    void write(const Tensor::Base & values, const Vsize_t & start = {}, const Vptrdiff_t & stride = {}) const;

    void write_s(const Vstring & values, size_t start = 0, ptrdiff_t stride = 1) const;

    Tensor::NType read(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vptrdiff_t & stride = {}) const;

    std::optional< Tensor::NType > fill_value() const;

    void set_fill_value(const Tensor::Base & value) const;

    bool fill() const;

    void set_fill(bool fill) const;

    int endian() const;

    // endian: 0 to 2 (NC_ENDIAN_NATIVE, NC_ENDIAN_LITTLE, NC_ENDIAN_BIG)
    void set_endian(int endian);

    bool checksum() const;

    void set_checksum(bool checksum) const;

    Vint deflate() const;

    // level: 0 to 9
    void set_deflate(bool shuffle, bool deflate, int level) const;

    Vint quantize() const;

    // quantize: 0 to 3 (NC_NOQUANTIZE, NC_QUANTIZE_BITGROOM, NC_QUANTIZE_GRANULARBR, NC_QUANTIZE_BITROUND)
    // nsd: 1 to 7 (float) or 15 (double)
    void set_quantize(int quantize, int nsd) const;

    Vsize_t chunking() const;

    // storage: 0 to 4 (NC_CHUNKED, NC_CONTIGUOUS, NC_COMPACT, NC_UNKNOWN_STORAGE, NC_VIRTUAL)
    void set_chunking(int storage, const Vsize_t & chunk_sizes) const;

    vector< std::variant< size_t, float >> chunk_cache() const;

    // preemption: 0.0 to 1.0
    void set_chunk_cache(size_t size, size_t slots, float preemption) const;

    private:

    int type_id() const;
  };
}
