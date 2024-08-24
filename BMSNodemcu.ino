
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define FIREBASE_AUTH "sdasdasd" //Your Firebase Web API Key
#define FIREBASE_HOST "asdasd" //Your Firebase URL
#define WIFI_SSID "asdasdasd.4"     //Your WIFI SSID
#define WIFI_PASSWORD "asdasdasdasd" //Your WIFI Password

bool RoomLEDStates[10] = {false, false, false, false, false, false, false, false, false, false};

void setup() {
  // Start Serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
  Serial.println(WiFi.localIP());

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Get boolean value from Firebase and print it
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
