/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: Content/info.proto
 */

// This file is generated. Please do not edit!
#ifndef CONTENT_INFO_H
#define CONTENT_INFO_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <Defines.h>
#include <limits>

// Include external proto definitions

namespace light_detector {

enum class InfoType : uint32_t
{
  Gain = 0,
  IntegralTime = 1
};

class InfoBusRequestContent final: public ::EmbeddedProto::MessageInterface
{
  public:
    InfoBusRequestContent() = default;
    InfoBusRequestContent(const InfoBusRequestContent& rhs )
    {
      set_infoType(rhs.get_infoType());
    }

    InfoBusRequestContent(const InfoBusRequestContent&& rhs ) noexcept
    {
      set_infoType(rhs.get_infoType());
    }

    ~InfoBusRequestContent() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      INFOTYPE = 1
    };

    InfoBusRequestContent& operator=(const InfoBusRequestContent& rhs)
    {
      set_infoType(rhs.get_infoType());
      return *this;
    }

    InfoBusRequestContent& operator=(const InfoBusRequestContent&& rhs) noexcept
    {
      set_infoType(rhs.get_infoType());
      return *this;
    }

    static constexpr char const* INFOTYPE_NAME = "infoType";
    inline void clear_infoType() { infoType_.clear(); }
    inline void set_infoType(const InfoType& value) { infoType_ = value; }
    inline void set_infoType(const InfoType&& value) { infoType_ = value; }
    inline const InfoType& get_infoType() const { return infoType_.get(); }
    inline InfoType infoType() const { return infoType_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<InfoType>(0) != infoType_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = infoType_.serialize_with_id(static_cast<uint32_t>(FieldNumber::INFOTYPE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::INFOTYPE:
            return_value = infoType_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_infoType();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::INFOTYPE:
          name = INFOTYPE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = infoType_.to_string(left_chars, indent_level + 2, INFOTYPE_NAME, true);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::enumeration<InfoType> infoType_ = static_cast<InfoType>(0);

};

class InfoBusResponseContent final: public ::EmbeddedProto::MessageInterface
{
  public:
    InfoBusResponseContent() = default;
    InfoBusResponseContent(const InfoBusResponseContent& rhs )
    {
      set_deviceId(rhs.get_deviceId());
      set_infoType(rhs.get_infoType());
      set_value(rhs.get_value());
      set_nonce(rhs.get_nonce());
    }

    InfoBusResponseContent(const InfoBusResponseContent&& rhs ) noexcept
    {
      set_deviceId(rhs.get_deviceId());
      set_infoType(rhs.get_infoType());
      set_value(rhs.get_value());
      set_nonce(rhs.get_nonce());
    }

    ~InfoBusResponseContent() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DEVICEID = 1,
      INFOTYPE = 2,
      VALUE = 3,
      NONCE = 4
    };

    InfoBusResponseContent& operator=(const InfoBusResponseContent& rhs)
    {
      set_deviceId(rhs.get_deviceId());
      set_infoType(rhs.get_infoType());
      set_value(rhs.get_value());
      set_nonce(rhs.get_nonce());
      return *this;
    }

    InfoBusResponseContent& operator=(const InfoBusResponseContent&& rhs) noexcept
    {
      set_deviceId(rhs.get_deviceId());
      set_infoType(rhs.get_infoType());
      set_value(rhs.get_value());
      set_nonce(rhs.get_nonce());
      return *this;
    }

    static constexpr char const* DEVICEID_NAME = "deviceId";
    inline void clear_deviceId() { deviceId_.clear(); }
    inline void set_deviceId(const uint32_t& value) { deviceId_ = value; }
    inline void set_deviceId(const uint32_t&& value) { deviceId_ = value; }
    inline uint32_t& mutable_deviceId() { return deviceId_.get(); }
    inline const uint32_t& get_deviceId() const { return deviceId_.get(); }
    inline uint32_t deviceId() const { return deviceId_.get(); }

    static constexpr char const* INFOTYPE_NAME = "infoType";
    inline void clear_infoType() { infoType_.clear(); }
    inline void set_infoType(const InfoType& value) { infoType_ = value; }
    inline void set_infoType(const InfoType&& value) { infoType_ = value; }
    inline const InfoType& get_infoType() const { return infoType_.get(); }
    inline InfoType infoType() const { return infoType_.get(); }

    static constexpr char const* VALUE_NAME = "value";
    inline void clear_value() { value_.clear(); }
    inline void set_value(const uint32_t& value) { value_ = value; }
    inline void set_value(const uint32_t&& value) { value_ = value; }
    inline uint32_t& mutable_value() { return value_.get(); }
    inline const uint32_t& get_value() const { return value_.get(); }
    inline uint32_t value() const { return value_.get(); }

    static constexpr char const* NONCE_NAME = "nonce";
    inline void clear_nonce() { nonce_.clear(); }
    inline void set_nonce(const uint32_t& value) { nonce_ = value; }
    inline void set_nonce(const uint32_t&& value) { nonce_ = value; }
    inline uint32_t& mutable_nonce() { return nonce_.get(); }
    inline const uint32_t& get_nonce() const { return nonce_.get(); }
    inline uint32_t nonce() const { return nonce_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != deviceId_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = deviceId_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DEVICEID), buffer, false);
      }

      if((static_cast<InfoType>(0) != infoType_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = infoType_.serialize_with_id(static_cast<uint32_t>(FieldNumber::INFOTYPE), buffer, false);
      }

      if((0U != value_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = value_.serialize_with_id(static_cast<uint32_t>(FieldNumber::VALUE), buffer, false);
      }

      if((0U != nonce_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = nonce_.serialize_with_id(static_cast<uint32_t>(FieldNumber::NONCE), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      FieldNumber id_tag = FieldNumber::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<FieldNumber>(id_number);
        switch(id_tag)
        {
          case FieldNumber::DEVICEID:
            return_value = deviceId_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::INFOTYPE:
            return_value = infoType_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::VALUE:
            return_value = value_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NONCE:
            return_value = nonce_.deserialize_check_type(buffer, wire_type);
            break;

          case FieldNumber::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_deviceId();
      clear_infoType();
      clear_value();
      clear_nonce();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DEVICEID:
          name = DEVICEID_NAME;
          break;
        case FieldNumber::INFOTYPE:
          name = INFOTYPE_NAME;
          break;
        case FieldNumber::VALUE:
          name = VALUE_NAME;
          break;
        case FieldNumber::NONCE:
          name = NONCE_NAME;
          break;
        default:
          name = "Invalid FieldNumber";
          break;
      }
      return name;
    }

#ifdef MSG_TO_STRING

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str) const
    {
      return this->to_string(str, 0, nullptr, true);
    }

    ::EmbeddedProto::string_view to_string(::EmbeddedProto::string_view& str, const uint32_t indent_level, char const* name, const bool first_field) const override
    {
      ::EmbeddedProto::string_view left_chars = str;
      int32_t n_chars_used = 0;

      if(!first_field)
      {
        // Add a comma behind the previous field.
        n_chars_used = snprintf(left_chars.data, left_chars.size, ",\n");
        if(0 < n_chars_used)
        {
          // Update the character pointer and characters left in the array.
          left_chars.data += n_chars_used;
          left_chars.size -= n_chars_used;
        }
      }

      if(nullptr != name)
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "\"%s\": {\n", name);
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s\"%s\": {\n", indent_level, " ", name);
        }
      }
      else
      {
        if( 0 == indent_level)
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "{\n");
        }
        else
        {
          n_chars_used = snprintf(left_chars.data, left_chars.size, "%*s{\n", indent_level, " ");
        }
      }
      
      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      left_chars = deviceId_.to_string(left_chars, indent_level + 2, DEVICEID_NAME, true);
      left_chars = infoType_.to_string(left_chars, indent_level + 2, INFOTYPE_NAME, false);
      left_chars = value_.to_string(left_chars, indent_level + 2, VALUE_NAME, false);
      left_chars = nonce_.to_string(left_chars, indent_level + 2, NONCE_NAME, false);
  
      if( 0 == indent_level) 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n}");
      }
      else 
      {
        n_chars_used = snprintf(left_chars.data, left_chars.size, "\n%*s}", indent_level, " ");
      }

      if(0 < n_chars_used)
      {
        left_chars.data += n_chars_used;
        left_chars.size -= n_chars_used;
      }

      return left_chars;
    }

#endif // End of MSG_TO_STRING

  private:


      EmbeddedProto::uint32 deviceId_ = 0U;
      EmbeddedProto::enumeration<InfoType> infoType_ = static_cast<InfoType>(0);
      EmbeddedProto::uint32 value_ = 0U;
      EmbeddedProto::uint32 nonce_ = 0U;

};

} // End of namespace light_detector
#endif // CONTENT_INFO_H