#include <iostream>
#include <sstream>
#include <string>
#include <dlib/server.h>

using namespace dlib;
using namespace std;

class web_server : public server_http {
  const std::string on_request(const incoming_things& incoming,
                               outgoing_things& outgoing);
};
