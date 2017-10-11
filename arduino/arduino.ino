/*
  Mur'oeuvre

  Code pour l'arduino. 
  Ce code fournit des fonctions afin de bouger les oeuvres
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Declaration des variables globales
bool deplacement_aleatoire 0
bool deplacement_commande 0
bool deplacement_maintenance 0
bool en_utilisation 0

int mur_actuel[] = {0, 0, 0, 0, 0, 0, 0, 0};
int mur_futur[] = {0, 0, 0, 0, 0, 0, 0, 0};
int future_emplacement_changer = 0;

YunServer server;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Bridge.begin();
  server.listenOnLocalhost();
  server.begin();
}

// the loop function runs over and over again forever
void loop() {
  YunClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  delay(50);
  if(en_utilisation)
  {
    if(deplacement_aleatoire)
    //call the right function
        //in use
    if(deplacement_commande)
    //call the right function
        //in use
    if(deplacement_maintenance)
    //call the right function
        //in use
    
  }
}

void process(YunClient client) {
  String command = client.readStringUntil('/');
  if (command == "maintenance") {
    maintenance(client);
  }
  if (command == "misemouvement") {
    misemouvement(client);
  }
  if (command == "status") {
    statusCommand(client);
  }
  if (command == "stop") {
    stop_mur();
  }
}

void maintenance(YunClient client) {

//manque vérification de la clés

stop_mur();

int valuex, valuey, valuez;
valuex = client.parseInt();
if (client.read() == '/') {
  valuey = client.parseInt();
}
if (client.read() == '/') {
  valuez = client.parseInt();
}

// bouger le mur à x y z
client.print(valuex);
client.print(F(","));
client.print(valuey);
client.print(F(","));
client.print(valuez);
client.print(F(","));
client.println(value);
}

void misemouvement(YunClient client) {
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
  client.print(F("status"));
  for (int emplacement = 0; emplacement < 8; emplacement++) {
    pin = DigitalPin[thisPin];
    value = digitalRead(pin);
    client.print(F("#"));
    client.print(mur_actuel[emplacement]);
  }
  client.println("");
}

void stop_mur() {
  
  client.println("bien joué");
}

