char msg[500];
void JSON_Pack() {
  const size_t capacity = 4 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5);
  if (MB_STS == 228) MB_STS_JSON = 0;
  else MB_STS_JSON = 1;
  DynamicJsonDocument doc(capacity);
  doc["MB_STS"] = MB_STS_JSON;
  JsonObject Sensor = doc.createNestedObject("Sensor");
  Sensor["Residual_Chlorine"] = Data01;
  Sensor["HypoClorous_acid"] = Data02;
  Sensor["Electrode_Signal"] = Data03;
  Sensor["Temperature"] = Data04;

  serializeJson(doc, Serial);
  serializeJson(doc, msg);
  Serial.println();
  if (MQTT_Enable) client.publish("Tech_Sensor/Data/Json", msg);

  Gateway_Status = String(MB_STS);
  Residual_Chlorine = String(Data01);
  HypoClorous_acid = String(Data02);
  Electrode_Signal = String(Data03);
  Temperature = String(Data04);
  }
