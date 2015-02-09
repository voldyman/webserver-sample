#include "server.h"

const std::string
web_server::on_request(const incoming_things& incoming,
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


  if (incoming.path == "/form_handler")
  {
    sout << "<h2> Stuff from the query string </h2>" << endl;
    sout << "<br>  user = " << incoming.queries["user"] << endl;
    sout << "<br>  pass = " << incoming.queries["pass"] << endl;

    // save these form submissions as cookies.
    outgoing.cookies["user"] = incoming.queries["user"];
    outgoing.cookies["pass"] = incoming.queries["pass"];
  }


  // Echo any cookies back to the client browser
  sout << "<h2>Cookies the web browser sent to the server</h2>";
  for ( key_value_map::const_iterator ci = incoming.cookies.begin(); ci != incoming.cookies.end(); ++ci )
  {
    sout << "<br/>" << ci->first << " = " << ci->second << endl;
  }

  sout << "<br/><br/>";

  sout << "<h2>HTTP Headers the web browser sent to the server</h2>";
  // Echo out all the HTTP headers we received from the client web browser
  for ( key_value_map_ci::const_iterator ci = incoming.headers.begin(); ci != incoming.headers.end(); ++ci )
  {
    sout << "<br/>" << ci->first << ": " << ci->second << endl;
  }

  sout << "</body> </html>";

  return sout.str();
}
