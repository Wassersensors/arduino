

// Path should start with a slash, i.e. /hello/world
void makeGetRequest(WiFiClient client, String path) {
  client.println("GET " + path + " HTTP/1.1");
  client.println("Host: " + String(SERVER_ADDRESS));
  client.println("Connection: close");
  client.println(); // end HTTP request header
}

// Path should start with a slash, i.e. /hello/world
// Body should be stringified json.
void makePostRequest(WiFiClient client, String body, String path) {
  // send HTTP request header
  client.println("POST " + path + " HTTP/1.1");
  client.println("Host: " + String(SERVER_ADDRESS));
  client.println("Content-Type: application/json");
  client.println("Accept: */*");
  client.println("Cache-Control: no-cache");
  client.println("Accept-Encoding: gzip, deflate");
  client.println("Accept-Language: en-us");
  client.println("Content-Length: " + String(body.length()));
  client.println("Connection: close");
  client.println(); // end HTTP request header
  client.println(body);
}
