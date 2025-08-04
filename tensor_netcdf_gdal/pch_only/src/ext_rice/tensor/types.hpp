#pragma once

namespace Tensor {

  class Int32 : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< int32_t > slice;

      View() = delete;

      View(const std::gslice_array< int32_t > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const int32_t & value) const {
        this->slice = value;
      }
      void operator=(const Int32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const Int32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const Int32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const Int32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const Int32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    int32_t fill_value = 0;
    std::valarray< int32_t > array;

    explicit Int32(const Vsize_t & shape, const Oint32_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit Int32(const Vint32_t & values, const Vsize_t & shape, const Oint32_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    Int32() = delete;

    Int32(const Int32 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    Int32 & operator=(const Int32 & tensor) = delete;

    Int32 operator+(int32_t value) const {
      return Int32(array + value, shape, fill_value);
    }
    Int32 operator+(const Int32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int32(array + tensor.array, shape, fill_value);
    }
    Int32 operator-(int32_t value) const {
      return Int32(array - value, shape, fill_value);
    }
    Int32 operator-(const Int32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int32(array - tensor.array, shape, fill_value);
    }
    Int32 operator*(int32_t value) const {
      return Int32(array * value, shape, fill_value);
    }
    Int32 operator*(const Int32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int32(array * tensor.array, shape, fill_value);
    }
    Int32 operator/(int32_t value) const {
      return Int32(array / value, shape, fill_value);
    }
    Int32 operator/(const Int32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int32(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< int32_t * >(_data_); }
    auto data()    const { return reinterpret_cast< const int32_t * >(_data_); }
    auto values()  const { return Vint32_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const Int32 & >(tensor).begin());
    }

    Int32::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< int32_t >(array[slice]), shape);
    }

    Int32 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return Int32(array[slice], shape, fill_value);
    }

    Int32 & refill_value(int32_t fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    Int32 & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    Int32 & seq(const Oint32_t & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(int32_t);
    }

    static Int32 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      Int32 tensor(shape, g_cast< int32_t >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = static_cast< int32_t >(std::atoi(buffer));
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static Int32 atan2(const Int32 & y, const Int32 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return Int32(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    Int32 abs() const {
      return Int32(std::abs(array), shape, fill_value);
    }

    Int32 pow(int32_t exp) const {
      return Int32(std::pow(array, std::valarray< int32_t >(exp, size)), shape, fill_value);
    }

    Int32 exp() const {
      return Int32(std::exp(array), shape, fill_value);
    }

    Int32 log() const {
      return Int32(std::log(array), shape, fill_value);
    }

    Int32 log10() const {
      return Int32(std::log10(array), shape, fill_value);
    }

    Int32 sqrt() const {
      return Int32(std::sqrt(array), shape, fill_value);
    }

    Int32 sin() const {
      return Int32(std::sin(array), shape, fill_value);
    }

    Int32 cos() const {
      return Int32(std::cos(array), shape, fill_value);
    }

    Int32 tan() const {
      return Int32(std::tan(array), shape, fill_value);
    }

    Int32 asin() const {
      return Int32(std::asin(array), shape, fill_value);
    }

    Int32 acos() const {
      return Int32(std::acos(array), shape, fill_value);
    }

    Int32 atan() const {
      return Int32(std::atan(array), shape, fill_value);
    }

    Int32 sinh() const {
      return Int32(std::sinh(array), shape, fill_value);
    }

    Int32 cosh() const {
      return Int32(std::cosh(array), shape, fill_value);
    }

    Int32 tanh() const {
      return Int32(std::tanh(array), shape, fill_value);
    }

    private:

    Int32(std::valarray< int32_t > && array, const Vsize_t & shape, int32_t fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::Int32;
    }
  };

  inline Base::operator Int32 * () const {
    return dynamic_cast< Int32 * >(const_cast< Base * >(this));
  }

  inline Base::operator Int32 & () const {
    return dynamic_cast< Int32 & >(*const_cast< Base * >(this));
  }

  class Int64 : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< int64_t2 > slice;

      View() = delete;

      View(const std::gslice_array< int64_t2 > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const int64_t2 & value) const {
        this->slice = value;
      }
      void operator=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    int64_t2 fill_value = 0;
    std::valarray< int64_t2 > array;

    explicit Int64(const Vsize_t & shape, const Oint64_t2 & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit Int64(const Vint64_t2 & values, const Vsize_t & shape, const Oint64_t2 & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    Int64() = delete;

    Int64(const Int64 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    Int64 & operator=(const Int64 & tensor) = delete;

    Int64 operator+(int64_t2 value) const {
      return Int64(array + value, shape, fill_value);
    }
    Int64 operator+(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array + tensor.array, shape, fill_value);
    }
    Int64 operator-(int64_t2 value) const {
      return Int64(array - value, shape, fill_value);
    }
    Int64 operator-(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array - tensor.array, shape, fill_value);
    }
    Int64 operator*(int64_t2 value) const {
      return Int64(array * value, shape, fill_value);
    }
    Int64 operator*(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array * tensor.array, shape, fill_value);
    }
    Int64 operator/(int64_t2 value) const {
      return Int64(array / value, shape, fill_value);
    }
    Int64 operator/(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< int64_t2 * >(_data_); }
    auto data()    const { return reinterpret_cast< const int64_t2 * >(_data_); }
    auto values()  const { return Vint64_t2(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const Int64 & >(tensor).begin());
    }

    Int64::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< int64_t2 >(array[slice]), shape);
    }

    Int64 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return Int64(array[slice], shape, fill_value);
    }

    Int64 & refill_value(int64_t2 fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    Int64 & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    Int64 & seq(const Oint64_t2 & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(int64_t2);
    }

    static Int64 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      Int64 tensor(shape, g_cast< int64_t2 >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = std::atoll(buffer);
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static Int64 atan2(const Int64 & y, const Int64 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return Int64(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    Int64 abs() const {
      return Int64(std::abs(array), shape, fill_value);
    }

    Int64 pow(int64_t2 exp) const {
      return Int64(std::pow(array, std::valarray< int64_t2 >(exp, size)), shape, fill_value);
    }

    Int64 exp() const {
      return Int64(std::exp(array), shape, fill_value);
    }

    Int64 log() const {
      return Int64(std::log(array), shape, fill_value);
    }

    Int64 log10() const {
      return Int64(std::log10(array), shape, fill_value);
    }

    Int64 sqrt() const {
      return Int64(std::sqrt(array), shape, fill_value);
    }

    Int64 sin() const {
      return Int64(std::sin(array), shape, fill_value);
    }

    Int64 cos() const {
      return Int64(std::cos(array), shape, fill_value);
    }

    Int64 tan() const {
      return Int64(std::tan(array), shape, fill_value);
    }

    Int64 asin() const {
      return Int64(std::asin(array), shape, fill_value);
    }

    Int64 acos() const {
      return Int64(std::acos(array), shape, fill_value);
    }

    Int64 atan() const {
      return Int64(std::atan(array), shape, fill_value);
    }

    Int64 sinh() const {
      return Int64(std::sinh(array), shape, fill_value);
    }

    Int64 cosh() const {
      return Int64(std::cosh(array), shape, fill_value);
    }

    Int64 tanh() const {
      return Int64(std::tanh(array), shape, fill_value);
    }

    private:

    Int64(std::valarray< int64_t2 > && array, const Vsize_t & shape, int64_t2 fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::Int64;
    }
  };

  inline Base::operator Int64 * () const {
    return dynamic_cast< Int64 * >(const_cast< Base * >(this));
  }

  inline Base::operator Int64 & () const {
    return dynamic_cast< Int64 & >(*const_cast< Base * >(this));
  }

  class SFloat : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< float > slice;

      View() = delete;

      View(const std::gslice_array< float > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const float & value) const {
        this->slice = value;
      }
      void operator=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    float fill_value = Float::nan;
    std::valarray< float > array;

    explicit SFloat(const Vsize_t & shape, const Ofloat & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit SFloat(const Vfloat & values, const Vsize_t & shape, const Ofloat & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    SFloat() = delete;

    SFloat(const SFloat & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    SFloat & operator=(const SFloat & tensor) = delete;

    SFloat operator+(float value) const {
      return SFloat(array + value, shape, fill_value);
    }
    SFloat operator+(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array + tensor.array, shape, fill_value);
    }
    SFloat operator-(float value) const {
      return SFloat(array - value, shape, fill_value);
    }
    SFloat operator-(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array - tensor.array, shape, fill_value);
    }
    SFloat operator*(float value) const {
      return SFloat(array * value, shape, fill_value);
    }
    SFloat operator*(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array * tensor.array, shape, fill_value);
    }
    SFloat operator/(float value) const {
      return SFloat(array / value, shape, fill_value);
    }
    SFloat operator/(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< float * >(_data_); }
    auto data()    const { return reinterpret_cast< const float * >(_data_); }
    auto values()  const { return Vfloat(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const SFloat & >(tensor).begin());
    }

    SFloat::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< float >(array[slice]), shape);
    }

    SFloat slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return SFloat(array[slice], shape, fill_value);
    }

    SFloat & refill_value(float fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    SFloat & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    SFloat & seq(const Ofloat & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(float);
    }

    static SFloat from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      SFloat tensor(shape, g_cast< float >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = static_cast< float >(std::atof(buffer));
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static SFloat atan2(const SFloat & y, const SFloat & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return SFloat(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    SFloat abs() const {
      return SFloat(std::abs(array), shape, fill_value);
    }

    SFloat pow(float exp) const {
      return SFloat(std::pow(array, std::valarray< float >(exp, size)), shape, fill_value);
    }

    SFloat exp() const {
      return SFloat(std::exp(array), shape, fill_value);
    }

    SFloat log() const {
      return SFloat(std::log(array), shape, fill_value);
    }

    SFloat log10() const {
      return SFloat(std::log10(array), shape, fill_value);
    }

    SFloat sqrt() const {
      return SFloat(std::sqrt(array), shape, fill_value);
    }

    SFloat sin() const {
      return SFloat(std::sin(array), shape, fill_value);
    }

    SFloat cos() const {
      return SFloat(std::cos(array), shape, fill_value);
    }

    SFloat tan() const {
      return SFloat(std::tan(array), shape, fill_value);
    }

    SFloat asin() const {
      return SFloat(std::asin(array), shape, fill_value);
    }

    SFloat acos() const {
      return SFloat(std::acos(array), shape, fill_value);
    }

    SFloat atan() const {
      return SFloat(std::atan(array), shape, fill_value);
    }

    SFloat sinh() const {
      return SFloat(std::sinh(array), shape, fill_value);
    }

    SFloat cosh() const {
      return SFloat(std::cosh(array), shape, fill_value);
    }

    SFloat tanh() const {
      return SFloat(std::tanh(array), shape, fill_value);
    }

    private:

    SFloat(std::valarray< float > && array, const Vsize_t & shape, float fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::SFloat;
    }
  };

  inline Base::operator SFloat * () const {
    return dynamic_cast< SFloat * >(const_cast< Base * >(this));
  }

  inline Base::operator SFloat & () const {
    return dynamic_cast< SFloat & >(*const_cast< Base * >(this));
  }

  class DFloat : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< double > slice;

      View() = delete;

      View(const std::gslice_array< double > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const double & value) const {
        this->slice = value;
      }
      void operator=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    double fill_value = Float::nan;
    std::valarray< double > array;

    explicit DFloat(const Vsize_t & shape, const Odouble & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit DFloat(const Vdouble & values, const Vsize_t & shape, const Odouble & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    DFloat() = delete;

    DFloat(const DFloat & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    DFloat & operator=(const DFloat & tensor) = delete;

    DFloat operator+(double value) const {
      return DFloat(array + value, shape, fill_value);
    }
    DFloat operator+(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array + tensor.array, shape, fill_value);
    }
    DFloat operator-(double value) const {
      return DFloat(array - value, shape, fill_value);
    }
    DFloat operator-(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array - tensor.array, shape, fill_value);
    }
    DFloat operator*(double value) const {
      return DFloat(array * value, shape, fill_value);
    }
    DFloat operator*(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array * tensor.array, shape, fill_value);
    }
    DFloat operator/(double value) const {
      return DFloat(array / value, shape, fill_value);
    }
    DFloat operator/(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< double * >(_data_); }
    auto data()    const { return reinterpret_cast< const double * >(_data_); }
    auto values()  const { return Vdouble(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const DFloat & >(tensor).begin());
    }

    DFloat::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< double >(array[slice]), shape);
    }

    DFloat slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return DFloat(array[slice], shape, fill_value);
    }

    DFloat & refill_value(double fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    DFloat & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    DFloat & seq(const Odouble & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(double);
    }

    static DFloat from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      DFloat tensor(shape, g_cast< double >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = std::atof(buffer);
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static DFloat atan2(const DFloat & y, const DFloat & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return DFloat(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    DFloat abs() const {
      return DFloat(std::abs(array), shape, fill_value);
    }

    DFloat pow(double exp) const {
      return DFloat(std::pow(array, std::valarray< double >(exp, size)), shape, fill_value);
    }

    DFloat exp() const {
      return DFloat(std::exp(array), shape, fill_value);
    }

    DFloat log() const {
      return DFloat(std::log(array), shape, fill_value);
    }

    DFloat log10() const {
      return DFloat(std::log10(array), shape, fill_value);
    }

    DFloat sqrt() const {
      return DFloat(std::sqrt(array), shape, fill_value);
    }

    DFloat sin() const {
      return DFloat(std::sin(array), shape, fill_value);
    }

    DFloat cos() const {
      return DFloat(std::cos(array), shape, fill_value);
    }

    DFloat tan() const {
      return DFloat(std::tan(array), shape, fill_value);
    }

    DFloat asin() const {
      return DFloat(std::asin(array), shape, fill_value);
    }

    DFloat acos() const {
      return DFloat(std::acos(array), shape, fill_value);
    }

    DFloat atan() const {
      return DFloat(std::atan(array), shape, fill_value);
    }

    DFloat sinh() const {
      return DFloat(std::sinh(array), shape, fill_value);
    }

    DFloat cosh() const {
      return DFloat(std::cosh(array), shape, fill_value);
    }

    DFloat tanh() const {
      return DFloat(std::tanh(array), shape, fill_value);
    }

    private:

    DFloat(std::valarray< double > && array, const Vsize_t & shape, double fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::DFloat;
    }
  };

  inline Base::operator DFloat * () const {
    return dynamic_cast< DFloat * >(const_cast< Base * >(this));
  }

  inline Base::operator DFloat & () const {
    return dynamic_cast< DFloat & >(*const_cast< Base * >(this));
  }

  class UInt8 : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< uint8_t > slice;

      View() = delete;

      View(const std::gslice_array< uint8_t > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const uint8_t & value) const {
        this->slice = value;
      }
      void operator=(const UInt8 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const UInt8 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const UInt8 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const UInt8 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const UInt8 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    uint8_t fill_value = 0;
    std::valarray< uint8_t > array;

    explicit UInt8(const Vsize_t & shape, const Ouint8_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit UInt8(const Vuint8_t & values, const Vsize_t & shape, const Ouint8_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    UInt8() = delete;

    UInt8(const UInt8 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    UInt8 & operator=(const UInt8 & tensor) = delete;

    UInt8 operator+(uint8_t value) const {
      return UInt8(array + value, shape, fill_value);
    }
    UInt8 operator+(const UInt8 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt8(array + tensor.array, shape, fill_value);
    }
    UInt8 operator-(uint8_t value) const {
      return UInt8(array - value, shape, fill_value);
    }
    UInt8 operator-(const UInt8 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt8(array - tensor.array, shape, fill_value);
    }
    UInt8 operator*(uint8_t value) const {
      return UInt8(array * value, shape, fill_value);
    }
    UInt8 operator*(const UInt8 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt8(array * tensor.array, shape, fill_value);
    }
    UInt8 operator/(uint8_t value) const {
      return UInt8(array / value, shape, fill_value);
    }
    UInt8 operator/(const UInt8 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt8(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< uint8_t * >(_data_); }
    auto data()    const { return reinterpret_cast< const uint8_t * >(_data_); }
    auto values()  const { return Vuint8_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const UInt8 & >(tensor).begin());
    }

    UInt8::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< uint8_t >(array[slice]), shape);
    }

    UInt8 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return UInt8(array[slice], shape, fill_value);
    }

    UInt8 & refill_value(uint8_t fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    UInt8 & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    UInt8 & seq(const Ouint8_t & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(uint8_t);
    }

    static UInt8 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      UInt8 tensor(shape, g_cast< uint8_t >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = static_cast< uint8_t >(std::atoi(buffer));
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static UInt8 atan2(const UInt8 & y, const UInt8 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return UInt8(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    UInt8 abs() const {
      return UInt8(*this);
    }

    UInt8 pow(uint8_t exp) const {
      return UInt8(std::pow(array, std::valarray< uint8_t >(exp, size)), shape, fill_value);
    }

    UInt8 exp() const {
      return UInt8(std::exp(array), shape, fill_value);
    }

    UInt8 log() const {
      return UInt8(std::log(array), shape, fill_value);
    }

    UInt8 log10() const {
      return UInt8(std::log10(array), shape, fill_value);
    }

    UInt8 sqrt() const {
      return UInt8(std::sqrt(array), shape, fill_value);
    }

    UInt8 sin() const {
      return UInt8(std::sin(array), shape, fill_value);
    }

    UInt8 cos() const {
      return UInt8(std::cos(array), shape, fill_value);
    }

    UInt8 tan() const {
      return UInt8(std::tan(array), shape, fill_value);
    }

    UInt8 asin() const {
      return UInt8(std::asin(array), shape, fill_value);
    }

    UInt8 acos() const {
      return UInt8(std::acos(array), shape, fill_value);
    }

    UInt8 atan() const {
      return UInt8(std::atan(array), shape, fill_value);
    }

    UInt8 sinh() const {
      return UInt8(std::sinh(array), shape, fill_value);
    }

    UInt8 cosh() const {
      return UInt8(std::cosh(array), shape, fill_value);
    }

    UInt8 tanh() const {
      return UInt8(std::tanh(array), shape, fill_value);
    }

    private:

    UInt8(std::valarray< uint8_t > && array, const Vsize_t & shape, uint8_t fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::UInt8;
    }
  };

  inline Base::operator UInt8 * () const {
    return dynamic_cast< UInt8 * >(const_cast< Base * >(this));
  }

  inline Base::operator UInt8 & () const {
    return dynamic_cast< UInt8 & >(*const_cast< Base * >(this));
  }

  class UInt32 : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< uint32_t > slice;

      View() = delete;

      View(const std::gslice_array< uint32_t > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }

      void operator=(const uint32_t & value) const {
        this->slice = value;
      }
      void operator=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void operator+=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void operator-=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void operator*=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void operator/=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    };

    uint32_t fill_value = 0;
    std::valarray< uint32_t > array;

    explicit UInt32(const Vsize_t & shape, const Ouint32_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }

    explicit UInt32(const Vuint32_t & values, const Vsize_t & shape, const Ouint32_t & fill_value = nil):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }

    UInt32() = delete;

    UInt32(const UInt32 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }

    UInt32 & operator=(const UInt32 & tensor) = delete;

    UInt32 operator+(uint32_t value) const {
      return UInt32(array + value, shape, fill_value);
    }
    UInt32 operator+(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array + tensor.array, shape, fill_value);
    }
    UInt32 operator-(uint32_t value) const {
      return UInt32(array - value, shape, fill_value);
    }
    UInt32 operator-(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array - tensor.array, shape, fill_value);
    }
    UInt32 operator*(uint32_t value) const {
      return UInt32(array * value, shape, fill_value);
    }
    UInt32 operator*(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array * tensor.array, shape, fill_value);
    }
    UInt32 operator/(uint32_t value) const {
      return UInt32(array / value, shape, fill_value);
    }
    UInt32 operator/(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array / tensor.array, shape, fill_value);
    }

    auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    auto & operator[](size_t i)       { return array[i]; }
    auto & operator[](size_t i) const { return array[i]; }
    auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    auto & front()       { return array[0]; }
    auto & front() const { return array[0]; }
    auto & back()        { return array[size - 1]; }
    auto & back()  const { return array[size - 1]; }
    auto begin()         { return std::begin(array); }
    auto begin()   const { return std::begin(array); }
    auto end()           { return std::end(array); }
    auto end()     const { return std::end(array); }
    auto data()          { return reinterpret_cast< uint32_t * >(_data_); }
    auto data()    const { return reinterpret_cast< const uint32_t * >(_data_); }
    auto values()  const { return Vuint32_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const UInt32 & >(tensor).begin());
    }

    UInt32::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< uint32_t >(array[slice]), shape);
    }

    UInt32 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return UInt32(array[slice], shape, fill_value);
    }

    UInt32 & refill_value(uint32_t fill_value) {
      if (std::isnan(this->fill_value)) {
        if (std::isnan(fill_value)) return *this;
        for (size_t i = 0; auto && value : array) if (std::isnan(value)) array[i] = fill_value;
      } else {
        if (fill_value == this->fill_value) return *this;
        for (size_t i = 0; auto && value : array) if (value == this->fill_value) array[i] = fill_value;
      }
      this->fill_value = fill_value;
      return *this;
    }

    UInt32 & reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }

    UInt32 & seq(const Ouint32_t & start = nil) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }

    size_t type_size() const override {
      return sizeof(uint32_t);
    }

    static UInt32 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none) {
      if (values.front() != '{' || values.back() != '}' ) throw RuntimeError("malformed values string");
      bool new_value = false;
      char buffer[24 + 1]; // double + '\0'
      UInt32 tensor(shape, g_cast< uint32_t >(fill_value));
      auto data = tensor.data();
      for (size_t i = 0; auto && c : values) {
        switch (c) {
        case '{': case ' ':
          break;
        case ',': case '}':
          if (new_value) {
            new_value = false;
            buffer[i] = '\0';
            bool null = (buffer[0] == 'N' && buffer[1] == 'U');
            if (null) *(data++) = tensor.fill_value;
            else *(data++) = static_cast< uint32_t >(std::strtoul(buffer, nullptr, 10));
            i = 0;
          }
          break;
        default:
          new_value = true;
          buffer[i++] = c;
        }
      }
      return tensor;
    }

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const {
      auto data = this->data();
      auto as_null = nulls.value_or(false);
      auto isnan_nodata = std::isnan(fill_value);
      size_t dim_i = 0, dim_j;
      size_t dim_n = rank - 1;
      size_t counts[rank];
      std::memcpy(counts, shape.data(), rank * sizeof(size_t));
      std::stringstream sql;
      if (before) sql << before.value();
      while (true) {
        while (true) {
          sql << '{';
          if (dim_i == dim_n) break;
          ++dim_i;
        }
        while (true) {
          auto value = *data++;
          if (as_null)
            if (isnan_nodata) sql << (std::isnan(value)   ? "NULL" : std::format("{}", value));
            else              sql << (value == fill_value ? "NULL" : std::format("{}", value));
          else                sql << std::format("{}", value);
          if (--counts[dim_i] == 0) break;
          sql << ',';
        }
        while (true) {
          sql << '}';
          if (dim_i == 0) {
            if (after) sql << after.value();
            return std::string(sql.str().c_str());
          }
          if (--counts[dim_i - 1] != 0) {
            for (dim_j = dim_i; dim_j <= dim_n; ++dim_j) counts[dim_j] = shape[dim_j];
            sql << ',';
            break;
          }
          --dim_i;
        }
      }
    }

    std::string to_string(Osize_t limit = nil) const {
      std::stringstream stream;
      stream << "[";
      std::ranges::for_each(shape, [&stream, first = true](auto size) mutable {
        if (!first) stream << ",";
        else first = false;
        stream << size;
      });
      stream << "]";
      stream << to_sql();
      auto string = std::string(stream.str().c_str());
      if (!limit) return string;
      auto _limit_ = limit.value();
      if (string.size() <= _limit_) return string;
      return string.substr(0, _limit_) + "...";
    }

    static UInt32 atan2(const UInt32 & y, const UInt32 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return UInt32(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }

    UInt32 abs() const {
      return UInt32(*this);
    }

    UInt32 pow(uint32_t exp) const {
      return UInt32(std::pow(array, std::valarray< uint32_t >(exp, size)), shape, fill_value);
    }

    UInt32 exp() const {
      return UInt32(std::exp(array), shape, fill_value);
    }

    UInt32 log() const {
      return UInt32(std::log(array), shape, fill_value);
    }

    UInt32 log10() const {
      return UInt32(std::log10(array), shape, fill_value);
    }

    UInt32 sqrt() const {
      return UInt32(std::sqrt(array), shape, fill_value);
    }

    UInt32 sin() const {
      return UInt32(std::sin(array), shape, fill_value);
    }

    UInt32 cos() const {
      return UInt32(std::cos(array), shape, fill_value);
    }

    UInt32 tan() const {
      return UInt32(std::tan(array), shape, fill_value);
    }

    UInt32 asin() const {
      return UInt32(std::asin(array), shape, fill_value);
    }

    UInt32 acos() const {
      return UInt32(std::acos(array), shape, fill_value);
    }

    UInt32 atan() const {
      return UInt32(std::atan(array), shape, fill_value);
    }

    UInt32 sinh() const {
      return UInt32(std::sinh(array), shape, fill_value);
    }

    UInt32 cosh() const {
      return UInt32(std::cosh(array), shape, fill_value);
    }

    UInt32 tanh() const {
      return UInt32(std::tanh(array), shape, fill_value);
    }

    private:

    UInt32(std::valarray< uint32_t > && array, const Vsize_t & shape, uint32_t fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }

    void sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::UInt32;
    }
  };

  inline Base::operator UInt32 * () const {
    return dynamic_cast< UInt32 * >(const_cast< Base * >(this));
  }

  inline Base::operator UInt32 & () const {
    return dynamic_cast< UInt32 & >(*const_cast< Base * >(this));
  }
}
