#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sio_message.h>
#include <stdexcept>

using namespace rapidjson;

void convert(sio::message::ptr const &message, Document &doc, Value &value) {
  if (!message) {
    throw std::invalid_argument("Null message pointer provided");
  }
  switch (message->get_flag()) {
  case sio::message::flag::flag_null:
    value.SetNull();
    break;
  case sio::message::flag::flag_boolean:
    value.SetBool(message->get_bool());
    break;
  case sio::message::flag::flag_integer:
    value.SetInt(message->get_int());
    break;
  case sio::message::flag::flag_double:
    value.SetDouble(message->get_double());
    break;
  case sio::message::flag::flag_string:
    value.SetString(message->get_string().c_str(), doc.GetAllocator());
    break;
  case sio::message::flag::flag_array: {
    value.SetArray();
    auto array = message->get_vector();
    for (auto &item : array) {
      Value arrayItem;
      convert(item, doc, arrayItem);
      value.PushBack(arrayItem, doc.GetAllocator());
    }
  } break;
  case sio::message::flag::flag_object: {
    value.SetObject();
    auto obj = message->get_map();
    for (auto &kv : obj) {
      Value key(kv.first.c_str(), doc.GetAllocator());
      Value objValue;
      convert(kv.second, doc, objValue);
      value.AddMember(key, objValue, doc.GetAllocator());
    }
  } break;
  default:
    throw std::runtime_error("Unhandled message flag");
  }
}

std::string to_json(sio::message::ptr const &message) {
  Document doc;
  Value value;
  convert(message, doc, value);

  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  value.Accept(writer);

  return buffer.GetString();
}
