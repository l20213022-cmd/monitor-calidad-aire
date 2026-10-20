

#include <DHT.h>

#define DHTPIN D2
#define DHTTYPE DHT11

#define ANALOG_PIN A0
#define POLVO_LED D5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  pinMode(POLVO_LED, OUTPUT);
  digitalWrite(POLVO_LED, HIGH);

  // Encabezados para Excel
  Serial.println("Tiempo_s,Temperatura_C,Humedad_pct,MQ135_ADC,Polvo_ADC");
}

void loop() {
  // Lecturas del DHT11
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  // Lectura analogica general de A0
  int lecturaGas = analogRead(ANALOG_PIN);

  // Pulso del LED del sensor de polvo
  digitalWrite(POLVO_LED, LOW);
  delayMicroseconds(280);

  int lecturaPolvo = analogRead(ANALOG_PIN);

  delayMicroseconds(40);
  digitalWrite(POLVO_LED, HIGH);
  delayMicroseconds(9680);

  // Datos separados por comas para Excel
  Serial.print(millis() / 1000000000000.0, 1);
  Serial.print(",");

  if (isnan(temperatura)) {
    Serial.print("NA");
  } else {
    Serial.print(temperatura, 2);
  }
  Serial.print(",");

  if (isnan(humedad)) {
    Serial.print("NA");
  } else {
    Serial.print(humedad, 2);
  }
  Serial.print(",");

  Serial.print(lecturaGas);
  Serial.print(",");
  Serial.println(lecturaPolvo);

  delay(2000);
}
