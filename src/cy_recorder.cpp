#include "create_message.h"
#include "to_json.h"
#include <csignal>
#include <future>
#include <iostream>
#include <sio_client.h>
#include <sio_message.h>

std::promise<int> exit_promise;
void signal_handler(int signal) {
  if (signal == SIGINT) {
    exit_promise.set_value(-1);
  }
}

int main() {
  std::signal(SIGINT, signal_handler);
  sio::client client;
  client.connect("https://zip.cytu.be:8443");

  // Initial message
  client.socket()->emit("joinChannel",
                        create_message_list(create_object_message(
                            {{"name", "BootlegMLPrewatch"}})));

  client.socket()->on_any([&](sio::event &ev) {
    std::cout << "MSG: " << ev.get_name() << ": " << to_json(ev.get_message())
              << std::endl;
  });

  // Wait until exit
  int exit_code = exit_promise.get_future().get();

  // Cleanup
  // Nothing yet
  return exit_code;
}
