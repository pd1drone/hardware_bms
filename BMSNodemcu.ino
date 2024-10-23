// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>


#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_AUTH "Ug0VVnHLdMDfZeLWn7GI5rbjBMSvsmzdSy3YmaqvB" //Your Firebase Web API Key
#define FIREBASE_HOST "iot-bms-f7f-default-rtdb.asia-southeast1.firebasedatabase.app" //Your Firebase URL


bool RoomLEDStates[10] = {false, false, false, false, false, false, false, false, false, false};


// Hostname
#define HOSTNAME "BMS"

// WiFi network created by ESP8266
const char* ssid = "BMS";
const char* password = "admin123";  // Add your password here

// Create server
WiFiServer server(80);

// Multicast DNS responder
MDNSResponder mdns;

bool Connected = false;

// Functions declaration
void connect_network(String wifiName, String wifiPassword);

void setup() {

  // Start Serial port
  Serial.begin(9600);
  delay(10);

  // Create WiFi network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);  // Use the password here

  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.softAPIP());

  // Start mDNS
  if (!MDNS.begin(HOSTNAME)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

  // Look for networks
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0)
    Serial.println("No networks found !! ");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");
}

void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("");
  Serial.println("New client");

  // Wait for data from client to become available
  while(client.connected() && !client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  //Serial.println(req);
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<html><head>";
  s += "</head>";
  s += "<body><div class=\"container\">";

  // Match the request
  if (req.indexOf("/login") != -1){

    Serial.println("Connecting to local network");

    // Parse response
    String wifiNameParameter = "wifiName=";
    String wifiPasswordParameter = "wifiPassword=";
    int indexName = req.indexOf(wifiNameParameter);
    int indexPassword = req.indexOf(wifiPasswordParameter);
    int indexBoard = req.indexOf("board=");

    String wifiName = req.substring(indexName + wifiNameParameter.length(), indexPassword - 1);
    String wifiPassword = req.substring(indexPassword + wifiPasswordParameter.length(), indexBoard - 1);

    Serial.print("WiFi name: ");
    Serial.println(wifiName);
    Serial.print("WiFi password: ");
    Serial.println(wifiPassword);

    // Build answer
    s += "<div>Logged in!</div>";
    s += "<div>Now please connect to the WiFi with internet to control BMS </div>";
    s += "</div></body></html>\r\n";

    // Send the response to the client
    client.print(s);
    //delay(100);
    client.stop();
    Serial.println("Client disonnected");

    // Connect to other network
    connect_network(wifiName, wifiPassword);

    // Do other things
    // Your code goes here

  }
  else {

    Serial.println("Serving interface");

    s += "<div>WiFi name: <input type='text' id='wname'></div>";
    s += "<div>WiFi password: <input type='text' id='pass'></div>";
    s += "<div><input class=\"btn\" type=\"button\" value=\"Validate\" onclick=\"login()\"></div>";
    s += "</div>";

    s += "<script>function login() {";
    s += "var wifiName = document.getElementById('wname').value;";
    s += "var wifiPassword = document.getElementById('pass').value;";
    s += "window.location.href = '/login?wifiName=' + wifiName + '&wifiPassword=' + wifiPassword + '&board=';}";
    s += "</script>";
    s += "</body></html>\r\n";

    // Send the response to the client
    client.print(s);
    //delay(100);
    client.stop();
    Serial.println("Client disconnected");
  }



  while (Connected){
      for (int i = 0; i < 10; i++) {
      String roomKey = "Room" + String(i + 1);
      RoomLEDStates[i] = Firebase.getBool(roomKey);
    }

    sendJSONResponse();

    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();
      
      if (command == "all on") {
        setAllLEDs(true); // Turn all LEDs on
      } else if (command == "all off") {
        setAllLEDs(false); // Turn all LEDs off
      } else {
        handleSerialCommand(command); // Handle other commands
      }
    }
  }

}

void connect_network(String wifiName, String wifiPassword) {

  // Connect to other network
  WiFi.mode(WIFI_STA);

  const char* other_ssid = wifiName.c_str();
  const char* other_password = wifiPassword.c_str();

  WiFi.begin(other_ssid, other_password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(other_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started");

  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Connected = true;
}

void handleSerialCommand(String command) {
  int roomNumber = command.substring(4, command.indexOf(' ')).toInt();
  // Extract action and convert to lowercase
  String action = command.substring(command.indexOf(' ') + 1);
  action.toLowerCase();

  String roomKey = "Room" + String(roomNumber);
  if (action == "on") {
    Firebase.setBool(roomKey, true);
  } else if (action == "off") {
    Firebase.setBool(roomKey, false);
  }

}

void setAllLEDs(bool state) {
  for (int i = 0; i < 10; i++) {
    String roomKey = "Room" + String(i + 1);
    Firebase.setBool(roomKey, state);
  }
}

void sendJSONResponse() {
  // Create a StaticJsonBuffer with an appropriate size
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& jsonDoc = jsonBuffer.createObject();

  // Populate the JSON document
  for (int i = 0; i < 10; i++) {
    String roomKey = "Room" + String(i + 1);
    jsonDoc[roomKey] = RoomLEDStates[i];
  }

  // Serialize JSON to String
  String jsonString;
  jsonDoc.printTo(jsonString);

  // Print JSON response
  Serial.println(jsonString);
}
