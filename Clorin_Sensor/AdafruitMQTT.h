boolean AdaMQTTSTS = LOW;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
Adafruit_MQTT_Client mqtt(&Adafruit_Client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
unsigned long AdaMqttDly;
String Topic[] = {"FCL", "Signal"};

//Topics
Adafruit_MQTT_Publish Residual_Chlorine_ada = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Residual_Chlorine_ada");
Adafruit_MQTT_Publish HypoClorous_acid_ada = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/HypoClorous_acid_ada");
Adafruit_MQTT_Publish Electrode_Signal_ada = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Electrode_Signal_ada");
Adafruit_MQTT_Publish Temperature_ada = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Temperatureada");

void  Adafruit_Connect();

void Adafruit_Post() {
  if ((millis() - AdaMqttDly) > AdaMqttDly_Window) {
    Adafruit_Connect();
    AdaMqttDly = millis();
    Webpabe_Update();
    ArduinoOTA.handle();
    if (AdaMQTTSTS) {
      Serial.println("Updating on Adafruit");
      if (! Residual_Chlorine_ada.publish(Data01)) {
        //Serial.println(F("Failed"));
      } else {
        //Serial.println(F("OK!"));
      }
      if (! HypoClorous_acid_ada.publish(Data02)) {
        //Serial.println(F("Failed"));
      } else {
        //Serial.println(F("OK!"));
      }
      if (! Electrode_Signal_ada.publish(Data03)) {
        //Serial.println(F("Failed"));
      } else {
        //Serial.println(F("OK!"));
      }
      if (! Temperature_ada.publish(Data04)) {
        //Serial.println(F("Failed"));
      } else {
        //Serial.println(F("OK!"));
      }
    }
    AdaMQTTSTS = LOW;
  }
}
void Adafruit_Connect() {
  ArduinoOTA.handle();
  int8_t ret;
  if (mqtt.connected()) {
    AdaMQTTSTS = HIGH;
    return;
  }
  Serial.println("Connecting to Adafruit MQTT... ");
  if ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    ArduinoOTA.handle();
    Serial.println("Adafruit MQTT not connected Retry interval is 5 minutes");
    AdaMQTTSTS = LOW;
  }
}
