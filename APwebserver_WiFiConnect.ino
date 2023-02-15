#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char *ssid = "ESP32_AP";
const char *password = "password";

WebServer server(80);
WebServer server2(80);

String inputSSID = "ROQUE EDICULA";
String inputPass = "01082002";

void handleRoot() {
  String html = "<html><body>"
                "<h1>ESP32 Web Server</h1>"
                "<form method='post'>"
                "<input type='text' name='input_ssid'>"
                "<input type='password' name='input_pass'>"
                "<input type='submit' value='Submit'>"
                "</form>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void handleRoot2() {
  String html = "<html><body>"
                "<h1>ESP32 Web Server</h1>"
                "asjhgfmasjkdf"
                "</form>"
                "</body></html>";
  server2.send(200, "text/html", html);
}



void handleSubmit() {
  inputSSID = server.arg("input_ssid");
  inputPass = server.arg("input_pass");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.println("Access Point IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.begin();
}

void loop() {
  server.handleClient();
  //handleSubmit();
  if (inputSSID != 0 && inputPass != 0) {
    server.stop();
    WiFi.begin(inputSSID.c_str(), inputPass.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server2.on("/", handleRoot2);
    server2.begin();
    while (1) {
      server2.handleClient();
    }
  }
}
