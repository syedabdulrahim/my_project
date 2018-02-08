  

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "shaolin";
const char* password = "Password@#password";
const char* mqtt_server = "192.168.1.5";
int x=0;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[5];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      client.publish("outTopic", "hello world1");
    } 
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  pinMode(5,INPUT);
  client.setServer(mqtt_server, 1883);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(2000);
     x=digitalRead(5);
        sprintf (msg,"%d",x);
        //x=digitalRead(5);
    Serial.println(x);
    client.publish("outTopic", msg);
  }
