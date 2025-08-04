// before_include
// include
#include "precompiled.hpp"
#include "all.hpp"

namespace NetCDF {
    Att::Att(int file_id, int var_id, std::string_view name):
      BelongsToFile(file_id, NULL_ID),
      var_id(var_id),
      name(name) {
    }
    void Att::copy(int file_id, int var_id, const string & name, int dst_file_id, int dst_var_id) {
      Base::check_status( nc_copy_att(file_id, var_id, name.c_str(), dst_file_id, dst_var_id) );
    }
    vector< Att > Att::all(int file_id, int var_id) {
      int count = 0;
      if (var_id == NC_GLOBAL) {
        Base::check_status( nc_inq_natts(file_id, &count), file_id, var_id );
      } else {
        Base::check_status( nc_inq_varnatts(file_id, var_id, &count), file_id, var_id );
      }
      vector< Att > atts(count);
      for (size_t i = 0; i < count; ++i) {
        char name[NC_MAX_NAME + 1];
        Base::check_status( nc_inq_attname(file_id, var_id, i, name), file_id, var_id );
        atts[i].file_id = file_id;
        atts[i].var_id = var_id;
        atts[i].name = string(name);
      }
      return atts;
    }
    Att Att::find(int file_id, int var_id, const string & name) {
      int id;
      Base::check_status( nc_inq_attid(file_id, var_id, name.c_str(), &id), file_id, var_id, name );
      return Att(file_id, var_id, name);
    }
    Att Att::write(int file_id, int var_id, const string & name, int type_id, const Tensor::Base & values, bool scalar) {
      if (type_id == NC_CHAR) throw TypeError();
      if (values.shape.size() != 1) throw TypeError();
      if (scalar && values.size != 1) throw TypeError();
      const void * data = values.data();
      Base::check_status( nc_put_att(file_id, var_id, name.c_str(), type_id, values.size, data), file_id, var_id, name );
      return Att(file_id, var_id, name);
    }
    Att Att::write_s(int file_id, int var_id, const string & name, const string & text, bool scalar) {
      if (scalar && text.size() != 1) throw TypeError();
      Base::check_status( nc_put_att_text(file_id, var_id, name.c_str(), text.size(), text.c_str()), file_id, var_id, name );
      return Att(file_id, var_id, name);
    }
    void Att::rename(const string & new_name) {
      check_status( nc_rename_att(file_id, var_id, name.c_str(), new_name.c_str()) );
      this->name = new_name;
    }
    Type Att::type() const {
      return NetCDF::type(type_id());
    }
    size_t Att::size() const {
      size_t size;
      check_status( nc_inq_attlen(file_id, var_id, name.c_str(), &size) );
      return size;
    }
    Tensor::NType Att::read() const {
      size_t count = size();
      switch (type_id()) {
      case NC_INT: {
        Tensor::Int32 numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_INT64: {
        Tensor::Int64 numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_FLOAT: {
        Tensor::SFloat numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_DOUBLE: {
        Tensor::DFloat numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_UBYTE: {
        Tensor::UInt8 numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_UINT: {
        Tensor::UInt32 numbers(Vsize_t{ count });
        check_status( nc_get_att(file_id, var_id, name.c_str(), numbers.Base::data()) );
        return numbers;
      }
      case NC_CHAR: {
        size_t count = size();
        char text[count + 1];
        text[count]= '\0';
        check_status( nc_get_att_text(file_id, var_id, name.c_str(), text) );
        return Vstring{ string(text) };
      }
      default:
        throw TypeError();
      }
    }
    void Att::destroy() const {
      check_status( nc_del_att(file_id, var_id, name.c_str()) );
    }
    void Att::check_status(int code, const std::stacktrace & trace, const std::source_location & source) const {
      Base::check_status(code, file_id, var_id, name, trace, source);
    }
    int Att::type_id() const {
      int type_id;
      check_status( nc_inq_atttype(file_id, var_id, name.c_str(), &type_id) );
      return type_id;
    }
}
