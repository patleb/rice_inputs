// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace Tensor {
      DFloat::View::View(const std::gslice_array< double > & slice, const Vsize_t & shape):
        size(Base::size_for(shape)),
        slice(slice) {
      }
      void DFloat::View::operator=(const double & value) const {
        this->slice = value;
      }
      void DFloat::View::operator=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice = tensor.array;
      }
      auto & DFloat::View::operator=(const View & view) const {
        if (size != view.size) throw RuntimeError("size[" S(size) "] != view.size[" S(view.size) "]");
        this->slice = view.slice;
        return *this;
      }
      void DFloat::View::operator+=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice += tensor.array;
      }
      void DFloat::View::operator-=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice -= tensor.array;
      }
      void DFloat::View::operator*=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice *= tensor.array;
      }
      void DFloat::View::operator/=(const DFloat & tensor) const {
        if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
        this->slice /= tensor.array;
      }
    DFloat::DFloat(const Vsize_t & shape, const Odouble & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(this->fill_value, this->size) {
      sync_refs();
    }
    DFloat::DFloat(const Vdouble & values, const Vsize_t & shape, const Odouble & fill_value):
      Base::Base(shape),
      fill_value(fill_value.value_or(Float::nan)),
      array(values.data(), values.size()) {
      if (values.size() != size) throw RuntimeError("values.size[" S(values.size()) "] != shape.total[" S(size) "]");
      sync_refs();
    }
    DFloat::DFloat(const DFloat & tensor):
      Base::Base(tensor),
      fill_value(tensor.fill_value),
      array(tensor.array) {
      sync_refs();
    }
    DFloat DFloat::operator+(double value) const {
      return DFloat(array + value, shape, fill_value);
    }
    DFloat DFloat::operator+(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array + tensor.array, shape, fill_value);
    }
    DFloat DFloat::operator-(double value) const {
      return DFloat(array - value, shape, fill_value);
    }
    DFloat DFloat::operator-(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array - tensor.array, shape, fill_value);
    }
    DFloat DFloat::operator*(double value) const {
      return DFloat(array * value, shape, fill_value);
    }
    DFloat DFloat::operator*(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array * tensor.array, shape, fill_value);
    }
    DFloat DFloat::operator/(double value) const {
      return DFloat(array / value, shape, fill_value);
    }
    DFloat DFloat::operator/(const DFloat & tensor) const {
      if (size != tensor.size) throw RuntimeError("size[" S(size) "] != tensor.size[" S(tensor.size) "]");
      return DFloat(array / tensor.array, shape, fill_value);
    }
    bool DFloat::operator==(const Tensor::Base & tensor) const {
      if (type != tensor.type) return false;
      if (shape != tensor.shape) return false;
      return std::equal(begin(), end(), dynamic_cast< const DFloat & >(tensor).begin());
    }
    DFloat::View DFloat::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return View(std::gslice_array< double >(array[slice]), shape);
    }
    DFloat DFloat::slice(const Vsize_t & start, const Vsize_t & count, const Vsize_t & stride) const {
      size_t offset = offset_for(start);
      auto counts = counts_or_ones(count);
      auto strides = counts_or_ones(stride);
      auto slice = std::gslice(offset, counts, strides);
      auto shape = Vsize_t(std::begin(counts), std::end(counts));
      return DFloat(array[slice], shape, fill_value);
    }
    DFloat & DFloat::refill_value(double fill_value) {
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
    DFloat & DFloat::reshape(const Vsize_t & shape) {
      Base::reshape(shape);
      return *this;
    }
    DFloat & DFloat::seq(const Odouble & start) {
      std::iota(begin(), end(), start.value_or(0));
      return *this;
    }
    size_t DFloat::type_size() const{
      return sizeof(double);
    }
    DFloat DFloat::from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value) {
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
    std::string DFloat::to_sql(const Ostring & before, const Ostring & after, Obool nulls) const {
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
    std::string DFloat::to_string(Osize_t limit) const {
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
    DFloat DFloat::atan2(const DFloat & y, const DFloat & x) {
      if (y.size != x.size) throw RuntimeError("y.size[" S(y.size) "] != x.size[" S(x.size) "]");
      return DFloat(std::atan2(y.array, x.array), y.shape, y.fill_value);
    }
    DFloat DFloat::abs() const {
      return DFloat(std::abs(array), shape, fill_value);
    }
    DFloat DFloat::pow(double exp) const {
      return DFloat(std::pow(array, std::valarray< double >(exp, size)), shape, fill_value);
    }
    DFloat DFloat::exp() const {
      return DFloat(std::exp(array), shape, fill_value);
    }
    DFloat DFloat::log() const {
      return DFloat(std::log(array), shape, fill_value);
    }
    DFloat DFloat::log10() const {
      return DFloat(std::log10(array), shape, fill_value);
    }
    DFloat DFloat::sqrt() const {
      return DFloat(std::sqrt(array), shape, fill_value);
    }
    DFloat DFloat::sin() const {
      return DFloat(std::sin(array), shape, fill_value);
    }
    DFloat DFloat::cos() const {
      return DFloat(std::cos(array), shape, fill_value);
    }
    DFloat DFloat::tan() const {
      return DFloat(std::tan(array), shape, fill_value);
    }
    DFloat DFloat::asin() const {
      return DFloat(std::asin(array), shape, fill_value);
    }
    DFloat DFloat::acos() const {
      return DFloat(std::acos(array), shape, fill_value);
    }
    DFloat DFloat::atan() const {
      return DFloat(std::atan(array), shape, fill_value);
    }
    DFloat DFloat::sinh() const {
      return DFloat(std::sinh(array), shape, fill_value);
    }
    DFloat DFloat::cosh() const {
      return DFloat(std::cosh(array), shape, fill_value);
    }
    DFloat DFloat::tanh() const {
      return DFloat(std::tanh(array), shape, fill_value);
    }
    DFloat::DFloat(std::valarray< double > && array, const Vsize_t & shape, double fill_value):
      Base::Base(shape),
      fill_value(fill_value),
      array(array) {
      sync_refs();
    }
    void DFloat::sync_refs() {
      this->nodata = reinterpret_cast< void * >(&fill_value);
      this->_data_ = reinterpret_cast< void * >(&array[0]);
      this->type = Tensor::Type::DFloat;
    }
}
