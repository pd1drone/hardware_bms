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

  server.on("/11on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 11, true);  // Call handleRoomAction for Room 11 ON
  });

  server.on("/11off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 11, false);  // Call handleRoomAction for Room 11 OFF
  });

  server.on("/12on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 12, true);  // Call handleRoomAction for Room 12 ON
  });

  server.on("/12off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 12, false);  // Call handleRoomAction for Room 12 OFF
  });

  server.on("/13on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 13, true);  // Call handleRoomAction for Room 13 ON
  });

  server.on("/13off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 13, false);  // Call handleRoomAction for Room 13 OFF
  });

  server.on("/14on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 14, true);  // Call handleRoomAction for Room 14 ON
  });

  server.on("/14off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 14, false);  // Call handleRoomAction for Room 14 OFF
  });

  server.on("/15on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 15, true);  // Call handleRoomAction for Room 15 ON
  });

  server.on("/15off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 15, false);  // Call handleRoomAction for Room 15 OFF
  });

  server.on("/16on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 16, true);  // Call handleRoomAction for Room 16 ON
  });

  server.on("/16off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 16, false);  // Call handleRoomAction for Room 16 OFF
  });

  server.on("/17on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 17, true);  // Call handleRoomAction for Room 17 ON
  });

  server.on("/17off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 17, false);  // Call handleRoomAction for Room 17 OFF
  });

  server.on("/18on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 18, true);  // Call handleRoomAction for Room 18 ON
  });

  server.on("/18off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 18, false);  // Call handleRoomAction for Room 18 OFF
  });

  server.on("/19on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 19, true);  // Call handleRoomAction for Room 19 ON
  });

  server.on("/19off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 19, false);  // Call handleRoomAction for Room 19 OFF
  });

  server.on("/20on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 20, true);  // Call handleRoomAction for Room 20 ON
  });

  server.on("/20off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 20, false);  // Call handleRoomAction for Room 20 OFF
  });

  server.on("/21on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 21, true);  // Call handleRoomAction for Room 21 ON
  });

  server.on("/21off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 21, false);  // Call handleRoomAction for Room 21 OFF
  });

  server.on("/22on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 22, true);  // Call handleRoomAction for Room 22 ON
  });

  server.on("/22off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 22, false);  // Call handleRoomAction for Room 22 OFF
  });

  server.on("/23on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 23, true);  // Call handleRoomAction for Room 23 ON
  });

  server.on("/23off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 23, false);  // Call handleRoomAction for Room 23 OFF
  });

  server.on("/24on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 24, true);  // Call handleRoomAction for Room 24 ON
  });

  server.on("/24off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 24, false);  // Call handleRoomAction for Room 24 OFF
  });

  server.on("/25on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 25, true);  // Call handleRoomAction for Room 25 ON
  });

  server.on("/25off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 25, false);  // Call handleRoomAction for Room 25 OFF
  });

  server.on("/26on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 26, true);  // Call handleRoomAction for Room 26 ON
  });

  server.on("/26off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 26, false);  // Call handleRoomAction for Room 26 OFF
  });

  server.on("/27on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 27, true);  // Call handleRoomAction for Room 27 ON
  });

  server.on("/27off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 27, false);  // Call handleRoomAction for Room 27 OFF
  });

  server.on("/28on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 28, true);  // Call handleRoomAction for Room 28 ON
  });

  server.on("/28off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 28, false);  // Call handleRoomAction for Room 28 OFF
  });

  server.on("/29on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 29, true);  // Call handleRoomAction for Room 29 ON
  });

  server.on("/29off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 29, false);  // Call handleRoomAction for Room 29 OFF
  });

  server.on("/30on", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 30, true);  // Call handleRoomAction for Room 30 ON
  });

  server.on("/30off", HTTP_GET, [](AsyncWebServerRequest *request) {
    handleRoomAction(request, 30, false);  // Call handleRoomAction for Room 30 OFF
  });


  server.begin();
}

void loop() {
  GetRoomStatusJSON();
}
