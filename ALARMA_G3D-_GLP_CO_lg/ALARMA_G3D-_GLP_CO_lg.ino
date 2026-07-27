
#include <ESP8266WiFi.h>
#include <Callmebot_ESP8266.h>

const char* ssid = "CuadrosGonzales";
const char* password = "PobreMorocho";

String phoneNumber = "+5493534064493";
String apiKey = "7793291";
#include <MQ2.h>

//change this with the pin that you use
int pin = A0;
float lpg, co, smoke;

MQ2 mq2(pin);


#define ledPin D4
#define BuzPin D8

int parametro = 300;
bool firstMessageSent = false;
const long ALARMA_INTERVALO = 2 * 60 * 1000; // 2 minutos en milisegundos
unsigned long tiempoAnterior = 0;

String messsage = "ALERTA PELIGRO, REVISAR AMBIENTE *** A *** !!!";
String messsage1 = " - Alarma G3D activada -";
String messsage2 = "Verificar sin hay pérdida de GAS, INCENDIO o MONOXIDO, POR FAVOR VENTILAR AMBIENTE !!!" ;


void setup() {
  Serial.begin(115200);
  // calibrate the device
  mq2.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED apagado al inicio
  pinMode(BuzPin, OUTPUT);
  analogWrite(BuzPin, 0);  // Buzzer apagado al inicio

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Callmebot.begin();
  Callmebot.whatsappMessage(phoneNumber, apiKey, messsage1);

  lpg = 0;
  co = 0;
  smoke = 0;


}

void loop() {
  lecturaMQ();
}
void lecturaMQ() {
  unsigned long tiempoActual = millis();
  /*
      read the values from the sensor, it returns
      an array which contains 3 values.
      0 : LPG in ppm
      1 : CO in ppm
      2 : SMOKE in ppm
  */
  float* values = mq2.read(true); //set it false if you don't want to print the values to the Serial

  lpg = values[0];
  //  lpg = mq2.readLPG();
  Serial.print("Valor analógico del sensor MQ-2: LGP ");
  Serial.print(lpg);
  Serial.println("ppm");
  co = values[1];
  Serial.print("Valor analógico del sensor MQ-2: co ");
  Serial.print(co);
  Serial.println("ppm");
  //  co = mq2.readCO();
  smoke = values[2];

  Serial.print("Valor analógico del sensor MQ-2: smoke ");
  Serial.print(smoke);
  Serial.println("ppm");
  // smoke = mq2.readSmoke();

  delay(1000);

  if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO && lpg >= parametro || co >= parametro || smoke >= parametro ) {
    // if (tiempoActual - tiempoAnterior >= ALARMA_INTERVALO) {
    // Disparar la alarma
    // Whatsapp Message
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage);
    Callmebot.whatsappMessage(phoneNumber, apiKey, messsage2);
    Serial.println(Callmebot.debug());
    Serial.println("¡ALARMA!");
    digitalWrite(ledPin, HIGH); // Enciende el pin de la alarma
    analogWrite(BuzPin, 250);  // Buzzer apagado al inicio
    delay(3000); // Dejar laanalogWrite(BuzPin, 0);  // Buzzer apagado al inicio alarma encendida por 1 segundo (ejemplo)
    digitalWrite(ledPin, LOW); // Apaga la alarma

    tiempoAnterior = tiempoActual; // Actualizar el tiempo anterior
  }

}
