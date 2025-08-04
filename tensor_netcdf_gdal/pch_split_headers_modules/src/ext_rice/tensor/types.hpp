#pragma once

namespace Tensor {

  class Int32 : public Base {
    public:

    class View {
      public:

      const size_t size;
      std::gslice_array< int32_t > slice;

      View() = delete;

      View(const std::gslice_array< int32_t > & slice, const Vsize_t & shape);

      void operator=(const int32_t & value) const;
      void operator=(const Int32 & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const Int32 & tensor) const;
      void operator-=(const Int32 & tensor) const;
      void operator*=(const Int32 & tensor) const;
      void operator/=(const Int32 & tensor) const;
    };

    int32_t fill_value = 0;
    std::valarray< int32_t > array;

    explicit Int32(const Vsize_t & shape, const Oint32_t & fill_value = nil);

    explicit Int32(const Vint32_t & values, const Vsize_t & shape, const Oint32_t & fill_value = nil);

    Int32() = delete;

    Int32(const Int32 & tensor);

    Int32 & operator=(const Int32 & tensor) = delete;

    Int32 operator+(int32_t value) const;
    Int32 operator+(const Int32 & tensor) const;
    Int32 operator-(int32_t value) const;
    Int32 operator-(const Int32 & tensor) const;
    Int32 operator*(int32_t value) const;
    Int32 operator*(const Int32 & tensor) const;
    Int32 operator/(int32_t value) const;
    Int32 operator/(const Int32 & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< int32_t * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const int32_t * >(_data_); }
    inline auto values()  const { return Vint32_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    Int32::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    Int32 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    Int32 & refill_value(int32_t fill_value);

    Int32 & reshape(const Vsize_t & shape);

    Int32 & seq(const Oint32_t & start = nil);

    size_t type_size() const override;

    static Int32 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static Int32 atan2(const Int32 & y, const Int32 & x);

    Int32 abs() const;

    Int32 pow(int32_t exp) const;

    Int32 exp() const;

    Int32 log() const;

    Int32 log10() const;

    Int32 sqrt() const;

    Int32 sin() const;

    Int32 cos() const;

    Int32 tan() const;

    Int32 asin() const;

    Int32 acos() const;

    Int32 atan() const;

    Int32 sinh() const;

    Int32 cosh() const;

    Int32 tanh() const;

    private:

    Int32(std::valarray< int32_t > && array, const Vsize_t & shape, int32_t fill_value);

    void sync_refs();
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

      View(const std::gslice_array< int64_t2 > & slice, const Vsize_t & shape);

      void operator=(const int64_t2 & value) const;
      void operator=(const Int64 & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const Int64 & tensor) const;
      void operator-=(const Int64 & tensor) const;
      void operator*=(const Int64 & tensor) const;
      void operator/=(const Int64 & tensor) const;
    };

    int64_t2 fill_value = 0;
    std::valarray< int64_t2 > array;

    explicit Int64(const Vsize_t & shape, const Oint64_t2 & fill_value = nil);

    explicit Int64(const Vint64_t2 & values, const Vsize_t & shape, const Oint64_t2 & fill_value = nil);

    Int64() = delete;

    Int64(const Int64 & tensor);

    Int64 & operator=(const Int64 & tensor) = delete;

    Int64 operator+(int64_t2 value) const;
    Int64 operator+(const Int64 & tensor) const;
    Int64 operator-(int64_t2 value) const;
    Int64 operator-(const Int64 & tensor) const;
    Int64 operator*(int64_t2 value) const;
    Int64 operator*(const Int64 & tensor) const;
    Int64 operator/(int64_t2 value) const;
    Int64 operator/(const Int64 & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< int64_t2 * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const int64_t2 * >(_data_); }
    inline auto values()  const { return Vint64_t2(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    Int64::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    Int64 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    Int64 & refill_value(int64_t2 fill_value);

    Int64 & reshape(const Vsize_t & shape);

    Int64 & seq(const Oint64_t2 & start = nil);

    size_t type_size() const override;

    static Int64 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static Int64 atan2(const Int64 & y, const Int64 & x);

    Int64 abs() const;

    Int64 pow(int64_t2 exp) const;

    Int64 exp() const;

    Int64 log() const;

    Int64 log10() const;

    Int64 sqrt() const;

    Int64 sin() const;

    Int64 cos() const;

    Int64 tan() const;

    Int64 asin() const;

    Int64 acos() const;

    Int64 atan() const;

    Int64 sinh() const;

    Int64 cosh() const;

    Int64 tanh() const;

    private:

    Int64(std::valarray< int64_t2 > && array, const Vsize_t & shape, int64_t2 fill_value);

    void sync_refs();
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

      View(const std::gslice_array< float > & slice, const Vsize_t & shape);

      void operator=(const float & value) const;
      void operator=(const SFloat & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const SFloat & tensor) const;
      void operator-=(const SFloat & tensor) const;
      void operator*=(const SFloat & tensor) const;
      void operator/=(const SFloat & tensor) const;
    };

    float fill_value = Float::nan;
    std::valarray< float > array;

    explicit SFloat(const Vsize_t & shape, const Ofloat & fill_value = nil);

    explicit SFloat(const Vfloat & values, const Vsize_t & shape, const Ofloat & fill_value = nil);

    SFloat() = delete;

    SFloat(const SFloat & tensor);

    SFloat & operator=(const SFloat & tensor) = delete;

    SFloat operator+(float value) const;
    SFloat operator+(const SFloat & tensor) const;
    SFloat operator-(float value) const;
    SFloat operator-(const SFloat & tensor) const;
    SFloat operator*(float value) const;
    SFloat operator*(const SFloat & tensor) const;
    SFloat operator/(float value) const;
    SFloat operator/(const SFloat & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< float * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const float * >(_data_); }
    inline auto values()  const { return Vfloat(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    SFloat::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    SFloat slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    SFloat & refill_value(float fill_value);

    SFloat & reshape(const Vsize_t & shape);

    SFloat & seq(const Ofloat & start = nil);

    size_t type_size() const override;

    static SFloat from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static SFloat atan2(const SFloat & y, const SFloat & x);

    SFloat abs() const;

    SFloat pow(float exp) const;

    SFloat exp() const;

    SFloat log() const;

    SFloat log10() const;

    SFloat sqrt() const;

    SFloat sin() const;

    SFloat cos() const;

    SFloat tan() const;

    SFloat asin() const;

    SFloat acos() const;

    SFloat atan() const;

    SFloat sinh() const;

    SFloat cosh() const;

    SFloat tanh() const;

    private:

    SFloat(std::valarray< float > && array, const Vsize_t & shape, float fill_value);

    void sync_refs();
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

      View(const std::gslice_array< double > & slice, const Vsize_t & shape);

      void operator=(const double & value) const;
      void operator=(const DFloat & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const DFloat & tensor) const;
      void operator-=(const DFloat & tensor) const;
      void operator*=(const DFloat & tensor) const;
      void operator/=(const DFloat & tensor) const;
    };

    double fill_value = Float::nan;
    std::valarray< double > array;

    explicit DFloat(const Vsize_t & shape, const Odouble & fill_value = nil);

    explicit DFloat(const Vdouble & values, const Vsize_t & shape, const Odouble & fill_value = nil);

    DFloat() = delete;

    DFloat(const DFloat & tensor);

    DFloat & operator=(const DFloat & tensor) = delete;

    DFloat operator+(double value) const;
    DFloat operator+(const DFloat & tensor) const;
    DFloat operator-(double value) const;
    DFloat operator-(const DFloat & tensor) const;
    DFloat operator*(double value) const;
    DFloat operator*(const DFloat & tensor) const;
    DFloat operator/(double value) const;
    DFloat operator/(const DFloat & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< double * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const double * >(_data_); }
    inline auto values()  const { return Vdouble(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    DFloat::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    DFloat slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    DFloat & refill_value(double fill_value);

    DFloat & reshape(const Vsize_t & shape);

    DFloat & seq(const Odouble & start = nil);

    size_t type_size() const override;

    static DFloat from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static DFloat atan2(const DFloat & y, const DFloat & x);

    DFloat abs() const;

    DFloat pow(double exp) const;

    DFloat exp() const;

    DFloat log() const;

    DFloat log10() const;

    DFloat sqrt() const;

    DFloat sin() const;

    DFloat cos() const;

    DFloat tan() const;

    DFloat asin() const;

    DFloat acos() const;

    DFloat atan() const;

    DFloat sinh() const;

    DFloat cosh() const;

    DFloat tanh() const;

    private:

    DFloat(std::valarray< double > && array, const Vsize_t & shape, double fill_value);

    void sync_refs();
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

      View(const std::gslice_array< uint8_t > & slice, const Vsize_t & shape);

      void operator=(const uint8_t & value) const;
      void operator=(const UInt8 & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const UInt8 & tensor) const;
      void operator-=(const UInt8 & tensor) const;
      void operator*=(const UInt8 & tensor) const;
      void operator/=(const UInt8 & tensor) const;
    };

    uint8_t fill_value = 0;
    std::valarray< uint8_t > array;

    explicit UInt8(const Vsize_t & shape, const Ouint8_t & fill_value = nil);

    explicit UInt8(const Vuint8_t & values, const Vsize_t & shape, const Ouint8_t & fill_value = nil);

    UInt8() = delete;

    UInt8(const UInt8 & tensor);

    UInt8 & operator=(const UInt8 & tensor) = delete;

    UInt8 operator+(uint8_t value) const;
    UInt8 operator+(const UInt8 & tensor) const;
    UInt8 operator-(uint8_t value) const;
    UInt8 operator-(const UInt8 & tensor) const;
    UInt8 operator*(uint8_t value) const;
    UInt8 operator*(const UInt8 & tensor) const;
    UInt8 operator/(uint8_t value) const;
    UInt8 operator/(const UInt8 & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< uint8_t * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const uint8_t * >(_data_); }
    inline auto values()  const { return Vuint8_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    UInt8::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    UInt8 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    UInt8 & refill_value(uint8_t fill_value);

    UInt8 & reshape(const Vsize_t & shape);

    UInt8 & seq(const Ouint8_t & start = nil);

    size_t type_size() const override;

    static UInt8 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static UInt8 atan2(const UInt8 & y, const UInt8 & x);

    UInt8 abs() const;

    UInt8 pow(uint8_t exp) const;

    UInt8 exp() const;

    UInt8 log() const;

    UInt8 log10() const;

    UInt8 sqrt() const;

    UInt8 sin() const;

    UInt8 cos() const;

    UInt8 tan() const;

    UInt8 asin() const;

    UInt8 acos() const;

    UInt8 atan() const;

    UInt8 sinh() const;

    UInt8 cosh() const;

    UInt8 tanh() const;

    private:

    UInt8(std::valarray< uint8_t > && array, const Vsize_t & shape, uint8_t fill_value);

    void sync_refs();
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

      View(const std::gslice_array< uint32_t > & slice, const Vsize_t & shape);

      void operator=(const uint32_t & value) const;
      void operator=(const UInt32 & tensor) const;
      auto & operator=(const View & view) const;
      void operator+=(const UInt32 & tensor) const;
      void operator-=(const UInt32 & tensor) const;
      void operator*=(const UInt32 & tensor) const;
      void operator/=(const UInt32 & tensor) const;
    };

    uint32_t fill_value = 0;
    std::valarray< uint32_t > array;

    explicit UInt32(const Vsize_t & shape, const Ouint32_t & fill_value = nil);

    explicit UInt32(const Vuint32_t & values, const Vsize_t & shape, const Ouint32_t & fill_value = nil);

    UInt32() = delete;

    UInt32(const UInt32 & tensor);

    UInt32 & operator=(const UInt32 & tensor) = delete;

    UInt32 operator+(uint32_t value) const;
    UInt32 operator+(const UInt32 & tensor) const;
    UInt32 operator-(uint32_t value) const;
    UInt32 operator-(const UInt32 & tensor) const;
    UInt32 operator*(uint32_t value) const;
    UInt32 operator*(const UInt32 & tensor) const;
    UInt32 operator/(uint32_t value) const;
    UInt32 operator/(const UInt32 & tensor) const;

    inline auto & operator()(size_t y, size_t x)       { return array[y * offsets[0] + x]; }
    inline auto & operator()(size_t y, size_t x) const { return array[y * offsets[0] + x]; }
    inline auto & operator[](size_t i)       { return array[i]; }
    inline auto & operator[](size_t i) const { return array[i]; }
    inline auto & operator[](const Vsize_t & indexes)       { return array[offset_for(indexes)]; }
    inline auto & operator[](const Vsize_t & indexes) const { return array[offset_for(indexes)]; }
    inline auto & front()       { return array[0]; }
    inline auto & front() const { return array[0]; }
    inline auto & back()        { return array[size - 1]; }
    inline auto & back()  const { return array[size - 1]; }
    inline auto begin()         { return std::begin(array); }
    inline auto begin()   const { return std::begin(array); }
    inline auto end()           { return std::end(array); }
    inline auto end()     const { return std::end(array); }
    inline auto data()          { return reinterpret_cast< uint32_t * >(_data_); }
    inline auto data()    const { return reinterpret_cast< const uint32_t * >(_data_); }
    inline auto values()  const { return Vuint32_t(begin(), end()); }

    // NOTE won't consider NaN --> use #to_sql
    bool operator==(const Tensor::Base & tensor) const;

    UInt32::View slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {});

    UInt32 slice(const Vsize_t & start = {}, const Vsize_t & count = {}, const Vsize_t & stride = {}) const;

    UInt32 & refill_value(uint32_t fill_value);

    UInt32 & reshape(const Vsize_t & shape);

    UInt32 & seq(const Ouint32_t & start = nil);

    size_t type_size() const override;

    static UInt32 from_sql(const std::string & values, const Vsize_t & shape, const GType & fill_value = none);

    std::string to_sql(const Ostring & before = nil, const Ostring & after = nil, Obool nulls = nil) const;

    std::string to_string(Osize_t limit = nil) const;

    static UInt32 atan2(const UInt32 & y, const UInt32 & x);

    UInt32 abs() const;

    UInt32 pow(uint32_t exp) const;

    UInt32 exp() const;

    UInt32 log() const;

    UInt32 log10() const;

    UInt32 sqrt() const;

    UInt32 sin() const;

    UInt32 cos() const;

    UInt32 tan() const;

    UInt32 asin() const;

    UInt32 acos() const;

    UInt32 atan() const;

    UInt32 sinh() const;

    UInt32 cosh() const;

    UInt32 tanh() const;

    private:

    UInt32(std::valarray< uint32_t > && array, const Vsize_t & shape, uint32_t fill_value);

    void sync_refs();
  };

  inline Base::operator UInt32 * () const {
    return dynamic_cast< UInt32 * >(const_cast< Base * >(this));
  }

  inline Base::operator UInt32 & () const {
    return dynamic_cast< UInt32 & >(*const_cast< Base * >(this));
  }
}
