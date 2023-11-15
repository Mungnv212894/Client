#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Sv 2022";
const char* password = "@sv22022";
const char* serverAddress = "Server_____";
const int serverPort = 8080;

#define LED_PIN 2
#define Pir 36
void connectToWiFi();

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  int pirValue = digitalRead(Pir);
  if(pirValue==HIGH)
  {
  int espId = 0; 
  int vol = analogRead(Pir); 
  time_t currentTime = time(nullptr);

  
  HTTPClient http;
  http.begin("http://" + String(serverAddress) + ":" + String(serverPort));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String postData = "esp-id=" + String(espId) + "&vol=" + String(vol) + "&time=" + String(currentTime);
  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    
    String response = http.getString();
    Serial.println(response);
    
    
    if (response.indexOf("HTTP/1.1 200 OK") != -1) {
      
       digitalWrite(LED_PIN, HIGH);
    }
  } else {
    Serial.print("HTTP Request failed, error: ");
    Serial.println(httpResponseCode);
    
  }

  http.end();
  }

  delay(5000);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}
