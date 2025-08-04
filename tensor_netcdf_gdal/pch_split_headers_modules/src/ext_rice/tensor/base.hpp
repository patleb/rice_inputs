#pragma once

namespace Tensor {
  enum class Type {
    Int32,
    Int64,
    SFloat,
    DFloat,
    UInt8,
    UInt32,
    Base
  };

  class Int32;
  class Int64;
  class SFloat;
  class DFloat;
  class UInt8;
  class UInt32;

  class Base {
    public:

    const size_t size;
    Vsize_t shape;
    Vsize_t offsets;
    size_t rank;
    void * nodata = nullptr;
    void * _data_ = nullptr;
    Tensor::Type type = Tensor::Type::Base;

    explicit Base(const Vsize_t & shape);

    Base() = delete;

    Base(const Base & tensor);

    Base & operator=(const Base & tensor) = delete;

    explicit operator Int32 * () const;
    explicit operator Int32 & () const;
    explicit operator Int64 * () const;
    explicit operator Int64 & () const;
    explicit operator SFloat * () const;
    explicit operator SFloat & () const;
    explicit operator DFloat * () const;
    explicit operator DFloat & () const;
    explicit operator UInt8 * () const;
    explicit operator UInt8 & () const;
    explicit operator UInt32 * () const;
    explicit operator UInt32 & () const;

    static size_t size_for(const Vsize_t & shape);

    GType nodata_value() const;

    inline auto _shape_()   const { return shape; }
    inline auto _offsets_() const { return offsets; }

    void reshape(const Vsize_t & shape);

    inline auto data()       { return _data_; }
    inline auto data() const { return _data_; }

    inline virtual size_t type_size() const { throw RuntimeError("not implemented error"); }

    protected:

    size_t offset_for(const Vsize_t & indexes) const;

    std::valarray< size_t > counts_or_ones(const Vsize_t & count) const;

    private:

    Vsize_t offsets_for(const Vsize_t & shape) const;
  };
}
