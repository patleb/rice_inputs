// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace Tensor {
      UInt32::View::View(const std::gslice_array< uint32_t > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }
      void UInt32::View::operator=(const uint32_t & value) const {
        this->slice = value;
      }
      void UInt32::View::operator=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & UInt32::View::operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void UInt32::View::operator+=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void UInt32::View::operator-=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void UInt32::View::operator*=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void UInt32::View::operator/=(const UInt32 & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    UInt32::UInt32(const Vsize_t & shape, const Ouint32_t & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(this->fill_value, this->size) {
      sync_refs();
    }
    UInt32::UInt32(const Vuint32_t & values, const Vsize_t & shape, const Ouint32_t & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(0)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }
    UInt32::UInt32(const UInt32 & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }
    UInt32 UInt32::operator+(uint32_t value) const {
      return UInt32(array + value, shape, fill_value);
    }
    UInt32 UInt32::operator+(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array + tensor.array, shape, fill_value);
    }
    UInt32 UInt32::operator-(uint32_t value) const {
      return UInt32(array - value, shape, fill_value);
    }
    UInt32 UInt32::operator-(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array - tensor.array, shape, fill_value);
    }
    UInt32 UInt32::operator*(uint32_t value) const {
      return UInt32(array * value, shape, fill_value);
    }
    UInt32 UInt32::operator*(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array * tensor.array, shape, fill_value);
    }
    UInt32 UInt32::operator/(uint32_t value) const {
      return UInt32(array / value, shape, fill_value);
    }
    UInt32 UInt32::operator/(const UInt32 & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return UInt32(array / tensor.array, shape, fill_value);
    }
    bool UInt32::operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const UInt32 & >(tensor).begin());
    }
    UInt32::View UInt32::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< uint32_t >(array[slice]), shape);
    }
    UInt32 UInt32::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return UInt32(array[slice], shape, fill_value);
    }
    UInt32 & UInt32::refill_value(uint32_t fill_value) {
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
    UInt32 & UInt32::reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }
    UInt32 & UInt32::seq(const Ouint32_t & start) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }
    size_t UInt32::type_size() const{
      return sizeof(uint32_t);
    }
    UInt32 UInt32::from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value) {
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
    std::string UInt32::to_sql(const Ostring & before, const Ostring & after, Obool nulls) const {
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
    std::string UInt32::to_string(Osize_t limit) const {
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
    UInt32 UInt32::atan2(const UInt32 & y, const UInt32 & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return UInt32(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }
    UInt32 UInt32::abs() const {
      return UInt32(*this);
    }
    UInt32 UInt32::pow(uint32_t exp) const {
      return UInt32(std::pow(array, std::valarray< uint32_t >(exp, size)), shape, fill_value);
    }
    UInt32 UInt32::exp() const {
      return UInt32(std::exp(array), shape, fill_value);
    }
    UInt32 UInt32::log() const {
      return UInt32(std::log(array), shape, fill_value);
    }
    UInt32 UInt32::log10() const {
      return UInt32(std::log10(array), shape, fill_value);
    }
    UInt32 UInt32::sqrt() const {
      return UInt32(std::sqrt(array), shape, fill_value);
    }
    UInt32 UInt32::sin() const {
      return UInt32(std::sin(array), shape, fill_value);
    }
    UInt32 UInt32::cos() const {
      return UInt32(std::cos(array), shape, fill_value);
    }
    UInt32 UInt32::tan() const {
      return UInt32(std::tan(array), shape, fill_value);
    }
    UInt32 UInt32::asin() const {
      return UInt32(std::asin(array), shape, fill_value);
    }
    UInt32 UInt32::acos() const {
      return UInt32(std::acos(array), shape, fill_value);
    }
    UInt32 UInt32::atan() const {
      return UInt32(std::atan(array), shape, fill_value);
    }
    UInt32 UInt32::sinh() const {
      return UInt32(std::sinh(array), shape, fill_value);
    }
    UInt32 UInt32::cosh() const {
      return UInt32(std::cosh(array), shape, fill_value);
    }
    UInt32 UInt32::tanh() const {
      return UInt32(std::tanh(array), shape, fill_value);
    }
    UInt32::UInt32(std::valarray< uint32_t > && array, const Vsize_t & shape, uint32_t fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }
    void UInt32::sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::UInt32;
    }
}
