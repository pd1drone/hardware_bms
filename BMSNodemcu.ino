#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebSrv.h>

const char *ssid = "BMS";
const char *password = "admin123";

String RoomStatusJson = "{}";

AsyncWebServer server(8081); // Set server to run on port 8081

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
    <h1>OK</h1>
</body>
</html>)rawliteral";

void GetRoomStatusJSON() {
  Serial.println("get");
  delay(300);
  if (Serial.available() > 0) {
    String responseFromArduino = Serial.readStringUntil('\n');
    responseFromArduino.trim();
    RoomStatusJson = responseFromArduino;
    //Serial.println(RoomStatusJson);
  }
}

void handleRoomAction(AsyncWebServerRequest *request, int roomNumber, bool isOn) {
  String message = "Room" + String(roomNumber) + (isOn ? " ON" : " OFF");
  Serial.println(message);

  AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
  response->addHeader("Access-Control-Allow-Origin", "*");
  response->addHeader("Access-Control-Allow-Methods", "GET");
  request->send(response);
}

void handleAllRoomsAction(AsyncWebServerRequest *request, bool isOn) {
  String message = isOn ? "all on" : "all off";
  Serial.println(message);

  AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
  response->addHeader("Access-Control-Allow-Origin", "*");
  response->addHeader("Access-Control-Allow-Methods", "GET");
  request->send(response);
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Handle CORS preflight requests
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncWebServerResponse *response = request->beginResponse(200);
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type");
    request->send(response);
  });

  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET");
    request->send(response);
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    //GetRoomStatusJSON();
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", RoomStatusJson);
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET");
    request->send(response);
  });

  server.on("/1on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 1, true);  // Call handleRoomAction for Room 1 ON
  });

  server.on("/1off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 1, false);  // Call handleRoomAction for Room 1 OFF
  });

  server.on("/2on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 2, true);  // Call handleRoomAction for Room 2 ON
  });

  server.on("/2off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 2, false);  // Call handleRoomAction for Room 2 OFF
  });

  server.on("/3on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 3, true);  // Call handleRoomAction for Room 3 ON
  });

  server.on("/3off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 3, false);  // Call handleRoomAction for Room 3 OFF
  });

  server.on("/4on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 4, true);  // Call handleRoomAction for Room 4 ON
  });

  server.on("/4off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 4, false);  // Call handleRoomAction for Room 4 OFF
  });

  server.on("/5on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 5, true);  // Call handleRoomAction for Room 5 ON
  });

  server.on("/5off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 5, false);  // Call handleRoomAction for Room 5 OFF
  });

  server.on("/6on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 6, true);  // Call handleRoomAction for Room 6 ON
  });

  server.on("/6off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 6, false);  // Call handleRoomAction for Room 6 OFF
  });

  server.on("/7on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 7, true);  // Call handleRoomAction for Room 7 ON
  });

  server.on("/7off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 7, false);  // Call handleRoomAction for Room 7 OFF
  });

  server.on("/8on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 8, true);  // Call handleRoomAction for Room 8 ON
  });

  server.on("/8off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 8, false);  // Call handleRoomAction for Room 8 OFF
  });

  server.on("/9on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 9, true);  // Call handleRoomAction for Room 9 ON
  });

  server.on("/9off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 9, false);  // Call handleRoomAction for Room 9 OFF
  });

  server.on("/10on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 10, true);  // Call handleRoomAction for Room 10 ON
  });

  server.on("/10off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 10, false);  // Call handleRoomAction for Room 10 OFF
  });

  server.on("/allon", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleAllRoomsAction(request, true);  // Handle all rooms ON
  });

  server.on("/alloff", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleAllRoomsAction(request, false);  // Handle all rooms OFF
  });

  server.begin();
}

void loop() {
  GetRoomStatusJSON();
}
