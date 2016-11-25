#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;



void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");

	char topicnr = topic[strlen(topic) - 1];
	int IntRow = topicnr - '0';
	Serial.print(" - detected row number: ");
	Serial.println(IntRow);

	lcd.setCursor(0, IntRow);
	lcd.print("                ");
	//lcd.clear();
	//lcd.setCursor(0, 0);
	//lcd.print(topic);

	for (int i = 0; i < length; i++) {
		

		Serial.print((char)payload[i]);
		lcd.setCursor(-1 + i + 1, IntRow);
		lcd.print((char)payload[i]);
	}
	Serial.println();



}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");

		lcd.setCursor(0, 1);
		lcd.print("MQTT connecting");

		// Create a random client ID
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (client.connect(clientId.c_str())) {
			Serial.println("connected");

			lcd.setCursor(0, 1);
			lcd.print("MQTT connected  ");

			// Once connected, publish an announcement...
			//client.publish("outTopic", "hello world");
			// ... and resubscribe
			


			char ConcatTopic[80];
			char WildCard[5] = "/#";
			sprintf(ConcatTopic,"%s%s", mqtt_topic, WildCard);
			lcd.setCursor(0, 1);
			lcd.print(ConcatTopic);
			Serial.println(ConcatTopic);
			
			client.subscribe(ConcatTopic);

		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			
			lcd.setCursor(0, 1);
			lcd.print("MQTT failed    ");

			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void mqttsetup() {
	int port = atoi(mqtt_port);
	client.setServer(mqtt_server, port);
	client.setCallback(callback);
}

void mqttloop() {

	if (!client.connected()) {
		reconnect();
	}
	client.loop();


}