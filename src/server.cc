#include "server.h"

const std::string
web_server::on_request(const incoming_things& incoming,
                       outgoing_things& outgoing)
{
  if (incoming.path == "/") {
    return index_handler(incoming, outgoing);

  } else if (incoming.path == "/form_handler") {
    return form_handler(incoming, outgoing);

  } else if (incoming.path == "/ipc") {
    return ipc_handler(incoming, outgoing);

  } else {
    return "404";
  }
}


const std::string
web_server::form_handler(const incoming_things& incoming,
                         outgoing_things& outgoing)
{
  ostringstream sout;

  sout << " <html> <body> "
       << "<form action='/form_handler' method='post'> "
       << "User Name: <input name='user' type='text'><br>  "
       << "User password: <input name='pass' type='text'> <input type='submit'> "
       << " </form>";

  sout << "<br>  path = "         << incoming.path << endl;
  sout << "<br>  request_type = " << incoming.request_type << endl;
  sout << "<br>  content_type = " << incoming.content_type << endl;
  sout << "<br>  protocol = "     << incoming.protocol << endl;
  sout << "<br>  foreign_ip = "   << incoming.foreign_ip << endl;
  sout << "<br>  foreign_port = " << incoming.foreign_port << endl;
  sout << "<br>  local_ip = "     << incoming.local_ip << endl;
  sout << "<br>  local_port = "   << incoming.local_port << endl;
  sout << "<br>  body = \""       << incoming.body << "\"" << endl;



  // Echo any cookies back to the client browser
  sout << "<h2>Cookies the web browser sent to the server</h2>";
  for ( key_value_map::const_iterator ci = incoming.cookies.begin(); ci != incoming.cookies.end(); ++ci )
  {
    sout << "<br/>" << ci->first << " = " << ci->second << endl;
  }

  sout << "<br/><br/>";

  sout << "<h2>HTTP Headers the web browser sent to the server</h2>";

  sout << "<h2> Stuff from the query string </h2>" << endl;
  sout << "<br>  user = " << incoming.queries["user"] << endl;
  sout << "<br>  pass = " << incoming.queries["pass"] << endl;

  // save these form submissions as cookies.
  outgoing.cookies["user"] = incoming.queries["user"];
  outgoing.cookies["pass"] = incoming.queries["pass"];

  for ( key_value_map_ci::const_iterator ci = incoming.headers.begin(); ci != incoming.headers.end(); ++ci )
  {
    sout << "<br/>" << ci->first << ": " << ci->second << endl;
  }

  sout << "</body> </html>";

  return sout.str();


}

const std::string
web_server::index_handler(const incoming_things& incoming,
                          outgoing_things& outgoing)
{
  ostringstream sout;
  sout << "<ol>"
       << "<li> <a href='/form_handler'>Form Handling </a></li>"
       << "<li> <a href='/ipc'> Inter Thread communication </a></li>"
       << endl;

  return sout.str();

}

const std::string
web_server::ipc_handler(const incoming_things& incoming,
                        outgoing_things& outgoing)
{
  if (incoming.request_type == "POST") {
    Message msg{incoming.queries["message"]};
    pipe->enqueue(msg);

    ostringstream sout;
    sout << "<meta http-equiv='refresh' content='3;url=/ipc'>";
    sout << "<body><b>Added message</b></body>";
    return sout.str();

  } else {
    ostringstream sout;
    sout << "<form action='/ipc' method='POST'>" << endl;
    sout << "Message <input type='text' name='message' /> <br>" << endl;
    sout << "<input type='submit' value='Send' />" << endl;
    return sout.str();
  }
}
