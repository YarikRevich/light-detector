/*
 *  This file is generated with Embedded Proto, PLEASE DO NOT EDIT!
 *  source: response.proto
 */

// This file is generated. Please do not edit!
#ifndef RESPONSE_H
#define RESPONSE_H

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
#include "Content/data.h"
#include "Content/info.h"
#include "Content/settings.h"

namespace light_detector {

class ResponseContainer final: public ::EmbeddedProto::MessageInterface
{
  public:
    ResponseContainer() = default;
    ResponseContainer(const ResponseContainer& rhs )
    {
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::DATABUS:
          set_dataBus(rhs.get_dataBus());
          break;

        case FieldNumber::INFOBUS:
          set_infoBus(rhs.get_infoBus());
          break;

        case FieldNumber::SETTINGSBUS:
          set_settingsBus(rhs.get_settingsBus());
          break;

        default:
          break;
      }

    }

    ResponseContainer(const ResponseContainer&& rhs ) noexcept
    {
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::DATABUS:
          set_dataBus(rhs.get_dataBus());
          break;

        case FieldNumber::INFOBUS:
          set_infoBus(rhs.get_infoBus());
          break;

        case FieldNumber::SETTINGSBUS:
          set_settingsBus(rhs.get_settingsBus());
          break;

        default:
          break;
      }

    }

    ~ResponseContainer() override = default;

    enum class FieldNumber : uint32_t
    {
      NOT_SET = 0,
      DATABUS = 1,
      INFOBUS = 2,
      SETTINGSBUS = 3
    };

    ResponseContainer& operator=(const ResponseContainer& rhs)
    {
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::DATABUS:
          set_dataBus(rhs.get_dataBus());
          break;

        case FieldNumber::INFOBUS:
          set_infoBus(rhs.get_infoBus());
          break;

        case FieldNumber::SETTINGSBUS:
          set_settingsBus(rhs.get_settingsBus());
          break;

        default:
          break;
      }

      return *this;
    }

    ResponseContainer& operator=(const ResponseContainer&& rhs) noexcept
    {
      if(rhs.get_which_content() != which_content_)
      {
        // First delete the old object in the oneof.
        clear_content();
      }

      switch(rhs.get_which_content())
      {
        case FieldNumber::DATABUS:
          set_dataBus(rhs.get_dataBus());
          break;

        case FieldNumber::INFOBUS:
          set_infoBus(rhs.get_infoBus());
          break;

        case FieldNumber::SETTINGSBUS:
          set_settingsBus(rhs.get_settingsBus());
          break;

        default:
          break;
      }

      return *this;
    }

    FieldNumber get_which_content() const { return which_content_; }

    static constexpr char const* DATABUS_NAME = "dataBus";
    inline bool has_dataBus() const
    {
      return FieldNumber::DATABUS == which_content_;
    }
    inline void clear_dataBus()
    {
      if(FieldNumber::DATABUS == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.dataBus_.~DataBusResponseContent();
      }
    }
    inline void set_dataBus(const DataBusResponseContent& value)
    {
      if(FieldNumber::DATABUS != which_content_)
      {
        init_content(FieldNumber::DATABUS);
      }
      content_.dataBus_ = value;
    }
    inline void set_dataBus(const DataBusResponseContent&& value)
    {
      if(FieldNumber::DATABUS != which_content_)
      {
        init_content(FieldNumber::DATABUS);
      }
      content_.dataBus_ = value;
    }
    inline DataBusResponseContent& mutable_dataBus()
    {
      if(FieldNumber::DATABUS != which_content_)
      {
        init_content(FieldNumber::DATABUS);
      }
      return content_.dataBus_;
    }
    inline const DataBusResponseContent& get_dataBus() const { return content_.dataBus_; }
    inline const DataBusResponseContent& dataBus() const { return content_.dataBus_; }

    static constexpr char const* INFOBUS_NAME = "infoBus";
    inline bool has_infoBus() const
    {
      return FieldNumber::INFOBUS == which_content_;
    }
    inline void clear_infoBus()
    {
      if(FieldNumber::INFOBUS == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.infoBus_.~InfoBusResponseContent();
      }
    }
    inline void set_infoBus(const InfoBusResponseContent& value)
    {
      if(FieldNumber::INFOBUS != which_content_)
      {
        init_content(FieldNumber::INFOBUS);
      }
      content_.infoBus_ = value;
    }
    inline void set_infoBus(const InfoBusResponseContent&& value)
    {
      if(FieldNumber::INFOBUS != which_content_)
      {
        init_content(FieldNumber::INFOBUS);
      }
      content_.infoBus_ = value;
    }
    inline InfoBusResponseContent& mutable_infoBus()
    {
      if(FieldNumber::INFOBUS != which_content_)
      {
        init_content(FieldNumber::INFOBUS);
      }
      return content_.infoBus_;
    }
    inline const InfoBusResponseContent& get_infoBus() const { return content_.infoBus_; }
    inline const InfoBusResponseContent& infoBus() const { return content_.infoBus_; }

    static constexpr char const* SETTINGSBUS_NAME = "settingsBus";
    inline bool has_settingsBus() const
    {
      return FieldNumber::SETTINGSBUS == which_content_;
    }
    inline void clear_settingsBus()
    {
      if(FieldNumber::SETTINGSBUS == which_content_)
      {
        which_content_ = FieldNumber::NOT_SET;
        content_.settingsBus_.~SettingsBusResponseContent();
      }
    }
    inline void set_settingsBus(const SettingsBusResponseContent& value)
    {
      if(FieldNumber::SETTINGSBUS != which_content_)
      {
        init_content(FieldNumber::SETTINGSBUS);
      }
      content_.settingsBus_ = value;
    }
    inline void set_settingsBus(const SettingsBusResponseContent&& value)
    {
      if(FieldNumber::SETTINGSBUS != which_content_)
      {
        init_content(FieldNumber::SETTINGSBUS);
      }
      content_.settingsBus_ = value;
    }
    inline SettingsBusResponseContent& mutable_settingsBus()
    {
      if(FieldNumber::SETTINGSBUS != which_content_)
      {
        init_content(FieldNumber::SETTINGSBUS);
      }
      return content_.settingsBus_;
    }
    inline const SettingsBusResponseContent& get_settingsBus() const { return content_.settingsBus_; }
    inline const SettingsBusResponseContent& settingsBus() const { return content_.settingsBus_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_content_)
      {
        case FieldNumber::DATABUS:
          if(has_dataBus() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.dataBus_.serialize_with_id(static_cast<uint32_t>(FieldNumber::DATABUS), buffer, true);
          }
          break;

        case FieldNumber::INFOBUS:
          if(has_infoBus() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.infoBus_.serialize_with_id(static_cast<uint32_t>(FieldNumber::INFOBUS), buffer, true);
          }
          break;

        case FieldNumber::SETTINGSBUS:
          if(has_settingsBus() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = content_.settingsBus_.serialize_with_id(static_cast<uint32_t>(FieldNumber::SETTINGSBUS), buffer, true);
          }
          break;

        default:
          break;
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
          case FieldNumber::DATABUS:
          case FieldNumber::INFOBUS:
          case FieldNumber::SETTINGSBUS:
            return_value = deserialize_content(id_tag, buffer, wire_type);
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
      clear_content();

    }

    static char const* field_number_to_name(const FieldNumber fieldNumber)
    {
      char const* name = nullptr;
      switch(fieldNumber)
      {
        case FieldNumber::DATABUS:
          name = DATABUS_NAME;
          break;
        case FieldNumber::INFOBUS:
          name = INFOBUS_NAME;
          break;
        case FieldNumber::SETTINGSBUS:
          name = SETTINGSBUS_NAME;
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

      left_chars = to_string_content(left_chars, indent_level + 2, true);
  
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



      FieldNumber which_content_ = FieldNumber::NOT_SET;
      union content
      {
        content() {}
        ~content() {}
        DataBusResponseContent dataBus_;
        InfoBusResponseContent infoBus_;
        SettingsBusResponseContent settingsBus_;
      };
      content content_;

      void init_content(const FieldNumber field_id)
      {
        if(FieldNumber::NOT_SET != which_content_)
        {
          // First delete the old object in the oneof.
          clear_content();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case FieldNumber::DATABUS:
            new(&content_.dataBus_) DataBusResponseContent;
            break;

          case FieldNumber::INFOBUS:
            new(&content_.infoBus_) InfoBusResponseContent;
            break;

          case FieldNumber::SETTINGSBUS:
            new(&content_.settingsBus_) SettingsBusResponseContent;
            break;

          default:
            break;
         }

         which_content_ = field_id;
      }

      void clear_content()
      {
        switch(which_content_)
        {
          case FieldNumber::DATABUS:
            ::EmbeddedProto::destroy_at(&content_.dataBus_);
            break;
          case FieldNumber::INFOBUS:
            ::EmbeddedProto::destroy_at(&content_.infoBus_);
            break;
          case FieldNumber::SETTINGSBUS:
            ::EmbeddedProto::destroy_at(&content_.settingsBus_);
            break;
          default:
            break;
        }
        which_content_ = FieldNumber::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_content(const FieldNumber field_id, 
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
        
        if(field_id != which_content_)
        {
          init_content(field_id);
        }

        switch(which_content_)
        {
          case FieldNumber::DATABUS:
            return_value = content_.dataBus_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::INFOBUS:
            return_value = content_.infoBus_.deserialize_check_type(buffer, wire_type);
            break;
          case FieldNumber::SETTINGSBUS:
            return_value = content_.settingsBus_.deserialize_check_type(buffer, wire_type);
            break;
          default:
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_content();
        }
        return return_value;
      }

#ifdef MSG_TO_STRING 
      ::EmbeddedProto::string_view to_string_content(::EmbeddedProto::string_view& str, const uint32_t indent_level, const bool first_field) const
      {
        ::EmbeddedProto::string_view left_chars = str;

        switch(which_content_)
        {
          case FieldNumber::DATABUS:
            left_chars = content_.dataBus_.to_string(left_chars, indent_level, DATABUS_NAME, first_field);
            break;
          case FieldNumber::INFOBUS:
            left_chars = content_.infoBus_.to_string(left_chars, indent_level, INFOBUS_NAME, first_field);
            break;
          case FieldNumber::SETTINGSBUS:
            left_chars = content_.settingsBus_.to_string(left_chars, indent_level, SETTINGSBUS_NAME, first_field);
            break;
          default:
            break;
        }

        return left_chars;
      }

#endif // End of MSG_TO_STRING
};

} // End of namespace light_detector
#endif // RESPONSE_H