#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
int dac = 0;
int DigitalPin[] = {2, 12, 13};
int DacPin = 3;
YunServer server;
void setup() {
pinMode(2,INPUT);
pinMode(4,INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(13, LOW);
Bridge.begin();
digitalWrite(13, HIGH);
server.listenOnLocalhost();
server.begin();
}
void loop() {
YunClient client = server.accept();
if (client) {
process(client);
client.stop();
}
delay(50);
}
void process(YunClient client) {
String command = client.readStringUntil('/');
if (command == "digital") {
digitalCommand(client);
}
if (command == "dac") {
dacCommand(client);
}
if (command == "status") {
statusCommand(client);
}
}
void digitalCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
digitalWrite(pin, value);
}
else {
value = digitalRead(pin);
}
client.print(F("digital,"));
client.print(pin);
client.print(F(","));
client.println(value);
}
void dacCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
dac = value;
analogWrite(pin, value);
}
else {
value = dac;
}
client.print(F("dac,"));
client.print(pin);
client.print(F(","));
client.println(value);
}
void statusCommand(YunClient client) {
int pin, value;
client.print(F("status"));
for (int thisPin = 0; thisPin < 3; thisPin++) {
pin = DigitalPin[thisPin];
value = digitalRead(pin);
client.print(F("#"));
client.print(pin);
client.print(F("="));
client.print(value);
}
{
pin = DacPin;
value = dac;
client.print(F("#"));
client.print(pin);
client.print(F("="));
client.print(value);
}
{
value = analogRead(0);
// convert the reading to millivolts:
      float voltage = value *  (5000/ 1024); 
      // convert the millivolts to temperature celsius:
      float temperature = (voltage - 500)/10;
client.print(F("#A0"));
client.print(F("="));
client.print(temperature);
}
client.println("");
}
