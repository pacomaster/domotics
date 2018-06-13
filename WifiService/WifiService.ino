#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <cstring>
#include <string.h>
const char* ssid     = "frankdomain"; 
const char* password = "codigodavinci";
const char* host     = "192.168.0.104"; // Your domain  
String path          = "/client/1/leds";
String pathTemp      = "/client/1/temp/";

const int pin0        = 0;
const int pin1        = 1;
const int pin2        = 2;
const int pin3        = 3;

int tempValue = 0;

void setup() 
{ 
  //Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY); // To use RX and TX as OUTPUT
  Serial.begin(115200);
  
	pinMode(pin0, OUTPUT);
	pinMode(pin2, OUTPUT);
  digitalWrite(pin0, HIGH);
  digitalWrite(pin1, HIGH);

  //pinMode(pin1, OUTPUT);
  //pinMode(pin3, OUTPUT); //INPUT
  //digitalWrite(pin2, HIGH);
  //digitalWrite(pin3, HIGH);  
	
	delay(10);
	//Serial.print("Connecting to ");
	//Serial.println(ssid);
	WiFi.begin(ssid, password);
	int wifi_ctr = 0;
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
	}
	//Serial.println("WiFi connected");
	//Serial.println("IP address: " + WiFi.localIP());
}

void loop() 
{
  submitTemp();

  readLeds();
}

void submitTemp() 
{
  if (Serial.available() > 0)
  {
    tempValue = Serial.parseInt();
    //Serial.print(tempValue);
    
    WiFiClient client;
    const int httpPort = 8080;    
    if (!client.connect(host, httpPort)) 
    {
      return;
    }

    if(tempValue > 0)
    {
    client.print(String("POST ") + pathTemp + tempValue + " HTTP/1.1\r\n" +               "Host: " + host + "\r\n" +                "Connection: keep-alive\r\n\r\n");
    }
  }
}

void readLeds() 
{
  //Serial.print("connecting to ");
  //Serial.println(host);
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) 
  {
    //Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +               "Host: " + host + "\r\n" +                "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
  // read response  
  String section="header";
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    // Serial.print(line);    // we’ll parse the HTML body here
    if (section=="header") 
    { // headers..
      //Serial.print(".");
      if (line=="\n") 
      { // skips the empty space at the beginning
        section="json";
      }
    }
    else if (section=="json") 
    {
      section="ignore";
      String result = line.substring(1);      // Parse JSON
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;

      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      
      if (!json_parsed.success())
      {
        //Serial.println("parseObject() failed");
        return;
      }
      else
      {   
        String str = json_parsed["status"];
        
        char * c = new char[str.length() + 1];        
        std::strcpy(c, str.c_str());
        int idx  = 0;
        char* token = strtok(c, ",");
        
        while (token)
        {
            if(*token == '0')
            {
              digitalWrite(idx, LOW);
            }
            else
            {
              digitalWrite(idx, HIGH);
            }            
            token = strtok(NULL, ",");
            idx++;
        }
      }
    }
  }
  //Serial.print("closing connection. ");
}
