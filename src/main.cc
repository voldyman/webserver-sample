#include <iostream>
#include <memory>
#include <thread>
#include <cstdlib>
#include <dlib/pipe.h>

#include "server.h"
#include "message.h"


void run_webserver(std::shared_ptr<dlib::pipe<Message>>& pipe) {
  try {
    web_server inventrom_server{pipe};
    inventrom_server.set_listening_port(8080);
    inventrom_server.start_async();

    std::cout << "Listening, http://localhost:8080/" << std::endl
              << "Press any key to exit" << std::endl;
    cin.get();
  } catch (exception& e) {
    std::cout << e.what() << std::endl;
  }

}


int main() {
  // create a pipe that can hold 100 messages 
  std::shared_ptr<dlib::pipe<Message>> ipc_pipe{new dlib::pipe<Message>{2}};

  // start the message pump in a separate thread
  std::thread t1([&ipc_pipe] () {
      Message msg;
      while (ipc_pipe->dequeue(msg)) {
        std::cout << msg.command << std::endl;
      }
    });

  // start the webserver
  run_webserver(ipc_pipe);

  // stop the pump, disable will make the dequeue return false
  ipc_pipe->disable();

  t1.join();

  return 0;
}
