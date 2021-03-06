#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>

int pino2 = 2;
bool estado_sensor;


//Define o endereço MAC que será utilizado
byte mac[] = {0x18, 0x51, 0xE9, 0xD8, 0x79, 0xB0};
boolean mensagem;

//Inicia o cliente Ethernet
EthernetClient client;

PubSubClient mqttClient(client);

void setup() {
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);
    
    mqttClient.setServer("54.144.190.205",1883);

    pinMode(pino2,INPUT_PULLUP);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");

}

void loop() {
  mqttClient.connect("miguelpierre");
    mensagem = mqttClient.publish( "miguelpierre-T", "Mensagem enviada" );
    //Serial.println(mensagem);

    estado_sensor = digitalRead(pino2);

  if (estado_sensor == 1)
  {
    mqttClient.connect("miguelpierre");
    mensagem = mqttClient.publish("miguelpierre-T", "Porta aberta ");    
    Serial.println("Porta aberta");
    Serial.println(estado_sensor);  
  }

   if (estado_sensor == 0)
  {
    mqttClient.connect("miguelpierre");
    mensagem = mqttClient.publish("miguelpierre-T", "Porta fechada ");
    Serial.println("Porta fechada");
    Serial.println(estado_sensor);
  }
    
    mqttClient.loop();
}



