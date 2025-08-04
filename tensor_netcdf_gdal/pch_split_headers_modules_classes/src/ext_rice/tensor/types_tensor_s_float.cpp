// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace Tensor {
      SFloat::View::View(const std::gslice_array< float > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }
      void SFloat::View::operator=(const float & value) const {
        this->slice = value;
      }
      void SFloat::View::operator=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & SFloat::View::operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void SFloat::View::operator+=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void SFloat::View::operator-=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void SFloat::View::operator*=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void SFloat::View::operator/=(const SFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    SFloat::SFloat(const Vsize_t & shape, const Ofloat & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(this->fill_value, this->size) {
      sync_refs();
    }
    SFloat::SFloat(const Vfloat & values, const Vsize_t & shape, const Ofloat & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }
    SFloat::SFloat(const SFloat & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }
    SFloat SFloat::operator+(float value) const {
      return SFloat(array + value, shape, fill_value);
    }
    SFloat SFloat::operator+(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array + tensor.array, shape, fill_value);
    }
    SFloat SFloat::operator-(float value) const {
      return SFloat(array - value, shape, fill_value);
    }
    SFloat SFloat::operator-(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array - tensor.array, shape, fill_value);
    }
    SFloat SFloat::operator*(float value) const {
      return SFloat(array * value, shape, fill_value);
    }
    SFloat SFloat::operator*(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array * tensor.array, shape, fill_value);
    }
    SFloat SFloat::operator/(float value) const {
      return SFloat(array / value, shape, fill_value);
    }
    SFloat SFloat::operator/(const SFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return SFloat(array / tensor.array, shape, fill_value);
    }
    bool SFloat::operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const SFloat & >(tensor).begin());
    }
    SFloat::View SFloat::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< float >(array[slice]), shape);
    }
    SFloat SFloat::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return SFloat(array[slice], shape, fill_value);
    }
    SFloat & SFloat::refill_value(float fill_value) {
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
    SFloat & SFloat::reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }
    SFloat & SFloat::seq(const Ofloat & start) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }
    size_t SFloat::type_size() const{
      return sizeof(float);
    }
    SFloat SFloat::from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value) {
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
    std::string SFloat::to_sql(const Ostring & before, const Ostring & after, Obool nulls) const {
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
    std::string SFloat::to_string(Osize_t limit) const {
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
    SFloat SFloat::atan2(const SFloat & y, const SFloat & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return SFloat(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }
    SFloat SFloat::abs() const {
      return SFloat(std::abs(array), shape, fill_value);
    }
    SFloat SFloat::pow(float exp) const {
      return SFloat(std::pow(array, std::valarray< float >(exp, size)), shape, fill_value);
    }
    SFloat SFloat::exp() const {
      return SFloat(std::exp(array), shape, fill_value);
    }
    SFloat SFloat::log() const {
      return SFloat(std::log(array), shape, fill_value);
    }
    SFloat SFloat::log10() const {
      return SFloat(std::log10(array), shape, fill_value);
    }
    SFloat SFloat::sqrt() const {
      return SFloat(std::sqrt(array), shape, fill_value);
    }
    SFloat SFloat::sin() const {
      return SFloat(std::sin(array), shape, fill_value);
    }
    SFloat SFloat::cos() const {
      return SFloat(std::cos(array), shape, fill_value);
    }
    SFloat SFloat::tan() const {
      return SFloat(std::tan(array), shape, fill_value);
    }
    SFloat SFloat::asin() const {
      return SFloat(std::asin(array), shape, fill_value);
    }
    SFloat SFloat::acos() const {
      return SFloat(std::acos(array), shape, fill_value);
    }
    SFloat SFloat::atan() const {
      return SFloat(std::atan(array), shape, fill_value);
    }
    SFloat SFloat::sinh() const {
      return SFloat(std::sinh(array), shape, fill_value);
    }
    SFloat SFloat::cosh() const {
      return SFloat(std::cosh(array), shape, fill_value);
    }
    SFloat SFloat::tanh() const {
      return SFloat(std::tanh(array), shape, fill_value);
    }
    SFloat::SFloat(std::valarray< float > && array, const Vsize_t & shape, float fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }
    void SFloat::sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::SFloat;
    }
}
