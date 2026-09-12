#define BLYNK_TEMPLATE_ID "TMPL3aJ9Ok3Zk"
#define BLYNK_TEMPLATE_NAME "FireBOT"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
BlynkTimer timer;
String rxFromMega = "";
#define V_MODE     V0
#define V_FWD      V1
#define V_BACK     V2
#define V_LEFT     V3
#define V_RIGHT    V4
#define V_PUMP     V5
#define V_NOZZLE   V6
#define V_SPEED    V7
#define V_STOP     V8
#define V_FIRESTR  V9   // textual fire alert (or value)
#define V_SMOKESTR V10
#define V_SMOKE    V11  // gauge/int
#define V_STATUS   V12  // extra status label for textual feedback
void sendToMega(const String &s) {
  Serial.print(s+'\n');
  //Serial.print('\n');
}
// Read serial data from ATmega and push to Blynk
void readMega() {
 

while (Serial.available()) {
    char c = (char)Serial.read();
    if (c == '\n') {
String line = rxFromMega;
      rxFromMega = "";
      line.trim();
      if (line.length() == 0) continue;
      if (line.startsWith("FIRE:")) {
        String val = line.substring(5);
        // two uses: write to V_FIRESTR and toggle V6 LED/flag if you used it
        Blynk.virtualWrite(V_FIRESTR, val);
 int flag = (val.indexOf('1') >= 0 || val.indexOf("Detected") >= 0) ? 1 : 0;
        Blynk.virtualWrite(V_NOZZLE, flag); 
        Blynk.virtualWrite(V_STATUS, String("FIRE: ") + val);
      } else if (line.startsWith("SMOKE:")) {
        String v = line.substring(6);
        int vi = v.toInt();
        Blynk.virtualWrite(V_SMOKE, vi);
        Blynk.virtualWrite(V_SMOKESTR, String("SMOKE: ") + vi);
      } else if (line.startsWith("STATUS:")) {
        String s = line.substring(7);
        Blynk.virtualWrite(V_STATUS, s);
      } else {
        // unknown -> show in status label
        Blynk.virtualWrite(V_STATUS, line);
      }
    } else if (c != '\r') {
      rxFromMega += c;
      if (rxFromMega.length() > 200) rxFromMega = \
rxFromMega.substring(rxFromMega.length()-200);
  
 
}
  }
}
BLYNK_WRITE(V_MODE) {
  int m = param.asInt();
  sendToMega(String("MODE:") + m);
}
BLYNK_WRITE(V_FWD) {
  if (param.asInt() == 1) sendToMega("FORWARD");
  else sendToMega("STOP");
}
BLYNK_WRITE(V_BACK) {
  if (param.asInt() == 1) sendToMega("BACKWARD");
  else sendToMega("STOP");
}
BLYNK_WRITE(V_LEFT) {
  if (param.asInt() == 1) sendToMega("LEFT");
  else sendToMega("STOP");
}
BLYNK_WRITE(V_RIGHT) {
  if (param.asInt() == 1) sendToMega("RIGHT");
  else sendToMega("STOP");
}
BLYNK_WRITE(V_STOP) {
  if (param.asInt() == 1) sendToMega("STOP");
}
BLYNK_WRITE(V_PUMP) {
  if (param.asInt() == 1) sendToMega("PUMP:ON");
  else sendToMega("PUMP:OFF");
}


BLYNK_WRITE(V_SPEED) {
  int s = param.asInt(); // expected 0-255
sendToMega(String("SPEED:") + s);
}
BLYNK_WRITE(V_NOZZLE) {
  int a = param.asInt(); // expected 0-180
  sendToMega(String("NOZZLE:") + a);
}
void setup() {
  Serial.begin(9600); // Serial to ATmega
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, readMega); // poll serial frequently
  Blynk.virtualWrite(V_STATUS, "ESP Bridge ready");
}
void loop() {
  Blynk.run();
  timer.run();
}
