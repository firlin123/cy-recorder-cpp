#include "create_message.h"
#include <rapidjson/document.h>

sio::message::ptr convert(const rapidjson::Value &value) {
  if (value.IsString()) {
    return create_string_message(value.GetString());
  } else if (value.IsBool()) {
    return create_bool_message(value.GetBool());
  } else if (value.IsInt64()) {
    return create_int_message(value.GetInt64());
  } else if (value.IsDouble()) {
    return create_double_message(value.GetDouble());
  } else if (value.IsNull()) {
    return create_null_message();
  } else if (value.IsArray()) {
    std::shared_ptr<sio::array_message> array =
        create_message<sio::array_message>();
    for (const auto &item : value.GetArray()) {
      array->push(convert(item));
    }
    return array;
  } else if (value.IsObject()) {
    std::shared_ptr<sio::object_message> object =
        create_message<sio::object_message>();
    for (auto it = value.MemberBegin(); it != value.MemberEnd(); ++it) {
      object->insert(it->name.GetString(), convert(it->value));
    }
    return object;
  }
  return nullptr;
}

sio::message::ptr from_json(const std::string &json_str) {
  rapidjson::Document doc;
  doc.Parse(json_str.c_str());
  return convert(doc);
}
