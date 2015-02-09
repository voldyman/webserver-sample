#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <dlib/server.h>
#include <dlib/pipe.h>

#include "message.h"

using namespace dlib;
using namespace std;

class web_server : public server_http {
  public:
    web_server(std::shared_ptr<dlib::pipe<Message>>& message_pipe) {
      pipe = message_pipe;
    }

  private:
    std::shared_ptr<dlib::pipe<Message>> pipe;

    const std::string on_request(const incoming_things& incoming,
                                 outgoing_things& outgoing);

    /* route handlers */
    const std::string index_handler(const incoming_things& incoming,
                                    outgoing_things& outgoing);

    const std::string ipc_handler(const incoming_things& incoming,
                                  outgoing_things& outgoing);

    const std::string form_handler(const incoming_things& incoming,
                                   outgoing_things& outgoing);
};
