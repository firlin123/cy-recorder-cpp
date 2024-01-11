#ifndef CREATE_MESSAGE_H_
#define CREATE_MESSAGE_H_
#include <sio_message.h>

template <typename T> std::shared_ptr<T> create_message() {
  return std::dynamic_pointer_cast<T>(T::create());
}
template <typename T, typename V> std::shared_ptr<T> create_message(V v) {
  return std::dynamic_pointer_cast<T>(T::create(v));
}
template <typename T>
std::shared_ptr<sio::object_message>
create_object_message(std::initializer_list<std::pair<std::string, T>> pairs) {
  auto obj = create_message<sio::object_message>();
  for (const std::pair<std::string, T> &pair : pairs) {
    obj->insert(pair.first, pair.second);
  }
  return obj;
}
inline std::shared_ptr<sio::object_message> create_object_message(
    std::initializer_list<std::pair<std::string, sio::message::ptr>> pairs) {
  return create_object_message<sio::message::ptr>(pairs);
}
inline std::shared_ptr<sio::object_message> create_object_message(
    std::initializer_list<std::pair<std::string, std::string>> pairs) {
  return create_object_message<std::string>(pairs);
}
inline std::shared_ptr<sio::object_message> create_object_message(
    std::initializer_list<std::pair<std::string, std::shared_ptr<std::string>>>
        pairs) {
  return create_object_message<std::shared_ptr<std::string>>(pairs);
}
inline std::shared_ptr<sio::null_message> create_null_message() {
  return create_message<sio::null_message>();
}
inline std::shared_ptr<sio::bool_message> create_bool_message(bool v) {
  return create_message<sio::bool_message, bool>(v);
}
inline std::shared_ptr<sio::int_message> create_int_message(int64_t v) {
  return create_message<sio::int_message, int64_t>(v);
}
inline std::shared_ptr<sio::double_message> create_double_message(double v) {
  return create_message<sio::double_message, double>(v);
}
inline std::shared_ptr<sio::string_message>
create_string_message(const std::string &v) {
  return create_message<sio::string_message, std::string const &>(v);
}
inline std::shared_ptr<sio::binary_message>
create_binary_message(const std::shared_ptr<const std::string> &v) {
  return create_message<sio::binary_message,
                        std::shared_ptr<const std::string> const &>(v);
}
template <typename T>
std::shared_ptr<sio::array_message>
create_array_message(std::initializer_list<T> messages) {
  auto arr = create_message<sio::array_message>();
  for (const T &message : messages) {
    arr->push(message);
  }
  return arr;
}
template <typename T>
sio::message::list create_message_list(std::initializer_list<T> messages) {
  sio::message::list msglist;
  for (const T &message : messages) {
    msglist.push(message);
  }
  return msglist;
}
template <typename T> sio::message::list create_message_list(T message) {
  return sio::message::list(message);
}
#endif