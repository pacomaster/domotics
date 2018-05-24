#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
const char* ssid     = "frankdomain"; 
const char* password = "codigodavinci";
const char* host      = "192.168.0.108"; // Your domain  
String path          = "/client/1/led/1";
const int pin        = 2;
void setup() {
    pinMode(pin, OUTPUT);
    pinMode(pin, HIGH);
    Serial.begin(115200);
  delay(5);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
    Serial.println("IP address: " + WiFi.localIP());
}
void loop() {
    Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +               "Host: " + host + "\r\n" +                "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
  // read response  
String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    // Serial.print(line);    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning
         section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      section="ignore";
      String result = line.substring(1);      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      else
      {
        String str = json_parsed["response"]["status"];
        if ( str == "0" )
        { 
          Serial.println("apagando foco: " + pin);
          digitalWrite(pin, LOW);
        }else
        {
          Serial.println("Prendiendo foco: " + pin);
          digitalWrite(pin, HIGH);
        }
        Serial.println(str);
      }
    }
  }
  Serial.print("closing connection. ");
}
