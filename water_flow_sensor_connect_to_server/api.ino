

// Path should start with a slash, i.e. /hello/world
void makeGetRequest(String path) {
  if (!client.connected()) {
    Serial.println("client is not connected, connecting again");
    makeConnection();
  }
  client.println("GET " + path + " HTTP/1.1");
  client.println("Host: " + String(SERVER_ADDRESS));
  client.println(); // end HTTP request header
}

// Path should start with a slash, i.e. /hello/world
// Body should be stringified json.
void makePostRequest(String path, String body) {
  if (!client.connected()) {
    Serial.println("client is not connected, connecting again");
    makeConnection();
  }
  // send HTTP request header
  client.println("POST " + path + " HTTP/1.1");
  client.println("Host: " + String(SERVER_ADDRESS));
  client.println("Content-Type: application/json");
  client.println("Accept: */*");
  client.println("Cache-Control: no-cache");
  client.println("Content-Length: " + String(body.length()));
  client.println(); // end HTTP request header
  client.println(body);
}

void makeConnection() {
  if (client.connectSSL(SERVER_ADDRESS, PORT)) {
    Serial.println("connected to pete");
  } else {
    Serial.println("connection to pete failed");
  }
}
