#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi configurations
const char *SSID = "STARVISION WIfi";  // Wifi SSID
const char *password = "0plmnko9";     // Wifi password

// ThingSpeak configuartion
const char *server = "http://api.thingspeak.com/update";
String apikey = "6BL5FO7MGKR32RV5";

void setup() {
  Serial.begin(115200);

  // connect to wifi
  WiFi.begin(SSID, password);
  Serial.print("Connecting to Wi-FI.....");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int rssi = WiFi.RSSI();  // storing Wi-Fi RSSI value nvarible called rssi in db

    // Printing RSSI value in Serial monitor
    Serial.print("RSSI:- ");
    Serial.println(rssi);

    HTTPClient http;
    // create an HTTp client object for making a request
    String url = server;
    url += "?api_key=" + apikey + "&field1=" + String(rssi);

    http.begin(url);                    // strat HTTP connection
    int httpResponseCode = http.GET();  // send GET request

    // verfiying this HTTP response validtiy
    if (httpResponseCode > 0) {
      Serial.print("ThingSpeak response:-");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error Sending Data:-");
      Serial.println(http.errorToString(httpResponseCode));
    }
    http.end();  //close HTTP conncetion
  } else {
    Serial.print("Wi-Fi is not connected");
  }
  delay(15000);
}
