#include <iostream>
#include "server.h"

int main() {
  try {
    web_server inventrom_server;
    inventrom_server.set_listening_port(8080);
    inventrom_server.start_async();

    std::cout << "Listening, http://localhost:8080/" << std::endl
              << "Press any key to exit" << std::endl;
    cin.get();
  } catch (exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
