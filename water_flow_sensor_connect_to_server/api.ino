

// Path should start with a slash, i.e. /hello/world
void makeGetRequest(String path) {
  if (client.connect(SERVER_ADDRESS, PORT)) {
    client.println("GET " + path + " HTTP/1.1");
    client.println("Host: " + String(SERVER_ADDRESS));
    client.println("Connection: close");
    client.println(); // end HTTP request header
  } else {
    Serial.println("connection to pete failed");
  }
}

// Path should start with a slash, i.e. /hello/world
// Body should be stringified json.
void makePostRequest(String path, String body) {
  if (client.connect(SERVER_ADDRESS, PORT)) {
    // send HTTP request header
    Serial.println("making post request: " + String(SERVER_ADDRESS));
    client.println("POST " + path + " HTTP/1.1");
    client.println("Host: " + String(SERVER_ADDRESS));
    client.println("Content-Type: application/json");
    client.println("Accept: */*");
    client.println("Cache-Control: no-cache");
    client.println("Content-Length: " + String(body.length()));
    client.println("Connection: close");
    client.println(); // end HTTP request header
    client.println(body);
  } else {
    Serial.println("connection to pete failed");
  } 
}
