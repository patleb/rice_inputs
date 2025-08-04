// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace Tensor {
    Base::Base(const Vsize_t & shape):
      size(size_for(shape)),
      shape(shape),
      offsets(offsets_for(shape)),
      rank(shape.size()) {
    }
    Base::Base(const Base & tensor):
      size(tensor.size),
      shape(tensor.shape),
      offsets(tensor.offsets),
      rank(tensor.rank) {
    }
    size_t Base::size_for(const Vsize_t & shape) {
      return std::ranges::fold_left(shape, 1, std::multiplies());
    }
    GType Base::nodata_value() const {
      switch (type) {
      case Tensor::Type::Int32: return g_cast(*reinterpret_cast< const int32_t * >(nodata));
      case Tensor::Type::Int64: return g_cast(*reinterpret_cast< const int64_t2 * >(nodata));
      case Tensor::Type::SFloat: return g_cast(*reinterpret_cast< const float * >(nodata));
      case Tensor::Type::DFloat: return g_cast(*reinterpret_cast< const double * >(nodata));
      case Tensor::Type::UInt8: return g_cast(*reinterpret_cast< const uint8_t * >(nodata));
      case Tensor::Type::UInt32: return g_cast(*reinterpret_cast< const uint32_t * >(nodata));
      default:
        throw RuntimeError("invalid Tensor::Type");
      }
    }
    void Base::reshape(const Vsize_t & shape) {
      auto total = size_for(shape);
      if (total != size) throw RuntimeError("shape.total[" S(total) "] != size[" S(size) "]");
      this->shape = shape;
      this->offsets = offsets_for(shape);
      this->rank = shape.size();
    }
    size_t Base::offset_for(const Vsize_t & indexes) const {
      size_t offset = 0;
      if (!indexes.empty()) {
        if (indexes.size() != rank) throw RuntimeError("indexes.size[" S(indexes.size()) "] != rank[" S(rank) "]");
        for (size_t i = 0; auto && index : indexes) {
          if (index >= shape[i]) throw RuntimeError("index[" S(index) "] >= shape[" S(shape[i]) "]");
          offset += index * offsets[i++];
        }
      }
      return offset;
    }
    std::valarray< size_t > Base::counts_or_ones(const Vsize_t & count) const {
      auto counts = count.empty() ? std::valarray< size_t >(1, rank) : std::valarray< size_t >(count.data(), count.size());
      if (counts.size() != rank) throw RuntimeError("count.size[" S(counts.size()) "] != rank[" S(rank) "]");
      return counts;
    }
    Vsize_t Base::offsets_for(const Vsize_t & shape) const {
      auto rank = shape.size();
      if (rank == 0) throw RuntimeError("at least one dimension must be defined");
      Vsize_t offsets(rank, 1);
      for (ssize_t i = rank - 2; i >= 0; --i) {
        auto & size = shape[i + 1];
        if (size == 0) throw RuntimeError("dimension [" S(i) "] is empty");
        offsets[i] = offsets[i + 1] * size;
      }
      if (shape.front() == 0) throw RuntimeError("first dimension is empty");
      return offsets;
    }
}
