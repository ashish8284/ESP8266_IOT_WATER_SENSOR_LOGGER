uint16_t CALL_STP = 0;
unsigned long Post_window = 0;
void ModbusCall() {
  if (!mb.slave()) {
    mb.readHreg(1, 0, MB_BF1, 10, cbWrite);
    for (uint16_t x = 0; x < 10 ; x++) {
      Serial.print(MB_BF1[x]); Serial.print(",");
    }
    Serial.println();
    ArduinoOTA.handle();
  }
  Data01 = MB_BF1[0];
  Data02 = MB_BF1[1];
  Data03 = MB_BF1[2];
  Data04 = MB_BF1[3];
  Data05 = MB_BF1[4];
  Data06 = MB_BF1[5];
  Data07 = MB_BF1[6];
  Data08 = MB_BF1[7];
  Data09 = MB_BF1[8];
  Data10 = MB_BF1[9];
  
  Serial.print(Data01);Serial.print(",");
  Serial.print(Data02);Serial.print(",");
  Serial.print(Data03);Serial.print(",");
  Serial.print(Data04);Serial.print(",");
  Serial.print(Data05);Serial.print(",");
  Serial.print(Data06);Serial.print(",");
  Serial.print(Data07);Serial.print(",");
  Serial.print(Data08);Serial.print(",");
  Serial.print(Data09);Serial.print(",");
  Serial.print(Data10);Serial.println();

  
  if (millis() - Post_window > Window_Time) {
    JSON_Pack();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Post_window += Window_Time;
    ArduinoOTA.handle();
    Webpabe_Update();
  }
}
