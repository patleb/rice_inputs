// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace Tensor {
      Int64::View::View(const std::gslice_array< int64_t2 > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }
      void Int64::View::operator=(const int64_t2 & value) const {
        this->slice = value;
      }
      void Int64::View::operator=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & Int64::View::operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void Int64::View::operator+=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void Int64::View::operator-=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void Int64::View::operator*=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void Int64::View::operator/=(const Int64 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    Int64::Int64(const Vsize_t & shape, const Oint64_t2 & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }
    Int64::Int64(const Vint64_t2 & values, const Vsize_t & shape, const Oint64_t2 & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }
    Int64::Int64(const Int64 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }
    Int64 Int64::operator+(int64_t2 value) const {
      return Int64(array + value, shape, fill_value);
    }
    Int64 Int64::operator+(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array + tensor.array, shape, fill_value);
    }
    Int64 Int64::operator-(int64_t2 value) const {
      return Int64(array - value, shape, fill_value);
    }
    Int64 Int64::operator-(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array - tensor.array, shape, fill_value);
    }
    Int64 Int64::operator*(int64_t2 value) const {
      return Int64(array * value, shape, fill_value);
    }
    Int64 Int64::operator*(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array * tensor.array, shape, fill_value);
    }
    Int64 Int64::operator/(int64_t2 value) const {
      return Int64(array / value, shape, fill_value);
    }
    Int64 Int64::operator/(const Int64 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return Int64(array / tensor.array, shape, fill_value);
    }
    bool Int64::operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const Int64 & >(tensor).begin());
    }
    Int64::View Int64::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< int64_t2 >(array[slice]), shape);
    }
    Int64 Int64::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return Int64(array[slice], shape, fill_value);
    }
    Int64 & Int64::refill_value(int64_t2 fill_value) {
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
    Int64 & Int64::reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }
    Int64 & Int64::seq(const Oint64_t2 & start) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }
    size_t Int64::type_size() const{
      return sizeof(int64_t2);
    }
    Int64 Int64::from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value) {
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
    std::string Int64::to_sql(const Ostring & before, const Ostring & after, Obool nulls) const {
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
    std::string Int64::to_string(Osize_t limit) const {
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
    Int64 Int64::atan2(const Int64 & y, const Int64 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return Int64(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }
    Int64 Int64::abs() const {
      return Int64(std::abs(array), shape, fill_value);
    }
    Int64 Int64::pow(int64_t2 exp) const {
      return Int64(std::pow(array, std::valarray< int64_t2 >(exp, size)), shape, fill_value);
    }
    Int64 Int64::exp() const {
      return Int64(std::exp(array), shape, fill_value);
    }
    Int64 Int64::log() const {
      return Int64(std::log(array), shape, fill_value);
    }
    Int64 Int64::log10() const {
      return Int64(std::log10(array), shape, fill_value);
    }
    Int64 Int64::sqrt() const {
      return Int64(std::sqrt(array), shape, fill_value);
    }
    Int64 Int64::sin() const {
      return Int64(std::sin(array), shape, fill_value);
    }
    Int64 Int64::cos() const {
      return Int64(std::cos(array), shape, fill_value);
    }
    Int64 Int64::tan() const {
      return Int64(std::tan(array), shape, fill_value);
    }
    Int64 Int64::asin() const {
      return Int64(std::asin(array), shape, fill_value);
    }
    Int64 Int64::acos() const {
      return Int64(std::acos(array), shape, fill_value);
    }
    Int64 Int64::atan() const {
      return Int64(std::atan(array), shape, fill_value);
    }
    Int64 Int64::sinh() const {
      return Int64(std::sinh(array), shape, fill_value);
    }
    Int64 Int64::cosh() const {
      return Int64(std::cosh(array), shape, fill_value);
    }
    Int64 Int64::tanh() const {
      return Int64(std::tanh(array), shape, fill_value);
    }
    Int64::Int64(std::valarray< int64_t2 > && array, const Vsize_t & shape, int64_t2 fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }
    void Int64::sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::Int64;
    }
}
