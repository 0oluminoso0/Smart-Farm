//libarise calling

#define BLYNK_TEMPLATE_ID "TMPLF9O8gGlp"
#define BLYNK_DEVICE_NAME "Garden1"
#define BLYNK_AUTH_TOKEN "ZHCw41rtYyaaQupE_8e6arorpgRTao9f"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "RAVEN";
char pass[] = "xy234786";

#define Relay1 19
#define Relay2 18
#define Relay3 5
#define PumpRelay 17
#define LEDpin 23
#define SoilSensor1 36
#define SoilSensor2 39
#define SoilSensor3 34
#define SoilSensor4 35
#define DHTPIN1 22
#define DHTPIN2 21
#define DHTTYPE DHT22
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

const int AirValue = 4000;
const int WaterValue = 1500;
int Soilpercent1 = 0;
int Soilpercent2 = 0;
int AdjustTemp1 = 40;
int AdjustTemp2 = 40;
int AdjustHumidity1 =35;
int AdjustHumidity2 = 35;
int AdjustSoil1 = 50;
int AdjustSoil2 = 50;

float h1;
float t1;
float h2;
float t2;
float Soil1;
float Soil2;
float Soil3;
float Soil4;
float AVGSoilGarden1;
float AVGSoilGarden2;
float AVGh;
float AVGt;

void setup()
{
  // Debug console
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(LEDpin, OUTPUT);
  pinMode(PumpRelay, OUTPUT);
  pinMode(SoilSensor1, INPUT);
  pinMode(SoilSensor2, INPUT);
  pinMode(SoilSensor3, INPUT);
  pinMode(SoilSensor4, INPUT);
  Serial.begin(115200);
  delay(1);

  Serial.println("Connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
    digitalWrite(LEDpin, HIGH);
    delay(100);
    digitalWrite(LEDpin, LOW);
    delay(100);
  }
  Serial.println("WiFi connected");
  Blynk.config(auth);
  dht1.begin();
  dht2.begin();
}

BLYNK_WRITE(V4)
{
  if (param.asInt() == 1)
  {
    digitalWrite(PumpRelay, HIGH);    
    digitalWrite(Relay1, HIGH);
  }
  if (AVGSoilGarden1 >= AdjustSoil1)
  {
    Blynk.virtualWrite(V4, 0);
    digitalWrite(Relay1, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, LOW);
    digitalWrite(Relay1, LOW);
  }
}
BLYNK_WRITE(V3)
{
  if (param.asInt() == 1)
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay3, HIGH);
  }
  if (AVGh >= AdjustHumidity1)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  if (AVGh >= AdjustHumidity2)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, LOW);
    digitalWrite(Relay3, LOW);
  }
}
BLYNK_WRITE(V14)
{
  if (param.asInt() == 1)
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay2, HIGH);
  }
  if (AVGSoilGarden2 >= AdjustSoil2)
  {
    digitalWrite(Relay2, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, LOW);
    digitalWrite(Relay2, LOW);
  }
}
BLYNK_WRITE(V11)
{
  AdjustTemp1 = param.asInt();
}
BLYNK_WRITE(V8)
{
  AdjustTemp2 = param.asInt();
}
BLYNK_WRITE(V12)
{
  AdjustHumidity1 = param.asInt();
}
BLYNK_WRITE(V9)
{
  AdjustHumidity2 = param.asInt();
}
BLYNK_WRITE(V13)
{
  AdjustSoil1 = param.asInt();
}
BLYNK_WRITE(V10)
{
  AdjustSoil2 = param.asInt();
}

void WaterGarden1()
{
  digitalWrite(PumpRelay, HIGH);
  digitalWrite(Relay1, HIGH);

  if (AVGSoilGarden1 >= AdjustSoil1)
  {
    Blynk.virtualWrite(V4, 0);
    digitalWrite(Relay1, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay1, HIGH);
  }
}
void WaterGarden2()
{
  Blynk.virtualWrite(V14, 0);
  digitalWrite(PumpRelay, HIGH);
  digitalWrite(Relay2, HIGH);
  
  if (AVGSoilGarden2 >= AdjustSoil2)
  {
    digitalWrite(Relay2, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay2, HIGH);
    
  }
}
void SprayHumidity()
{
  digitalWrite(PumpRelay, HIGH);
  digitalWrite(Relay3, HIGH);
  if (AVGh >= AdjustHumidity1)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  if (AVGh >= AdjustHumidity2)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay3, HIGH);
  }
}
void SprayTemp()
{
  digitalWrite(PumpRelay, HIGH);
  digitalWrite(Relay3, HIGH);
  if (AVGt >= AdjustTemp1)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  if (AVGt >= AdjustTemp2)
  {
    Blynk.virtualWrite(V3, 0);
    digitalWrite(Relay3, LOW);
    digitalWrite(PumpRelay, LOW);
  }
  else
  {
    digitalWrite(PumpRelay, HIGH);
    digitalWrite(Relay3, HIGH);
  }
}


void loop()
{
  Blynk.run();
  Blynk.virtualWrite(V11, AdjustTemp1);
  Blynk.virtualWrite(V8, AdjustTemp2);
  Blynk.virtualWrite(V12, AdjustHumidity1);
  Blynk.virtualWrite(V9, AdjustHumidity2);
  Blynk.virtualWrite(V13, AdjustSoil1);
  Blynk.virtualWrite(V10, AdjustSoil2);
  h1 = dht1.readHumidity();
  t1 = dht1.readTemperature();
  h2 = dht2.readHumidity();
  t2 = dht2.readTemperature();
  AVGh = (h1 + h2) / 2;
  AVGt = (t1 + t2) / 2;
  Soil1 = analogRead(SoilSensor1);
  Soil2 = analogRead(SoilSensor2);
  AVGSoilGarden1 = (Soil1 + Soil2) / 2;
  Soilpercent1 = map(AVGSoilGarden1, AirValue, WaterValue, 0, 100);
  Soil3 = analogRead(SoilSensor3);
  Soil4 = analogRead(SoilSensor4);
  AVGSoilGarden2 = (Soil3 + Soil4) / 2;
  Soilpercent2 = map(AVGSoilGarden2, AirValue, WaterValue, 0, 100);
  Blynk.virtualWrite(V0, t1);
  Blynk.virtualWrite(V1, h1);
  Blynk.virtualWrite(V5, t2);
  Blynk.virtualWrite(V6, h2);
  Blynk.virtualWrite(V2, Soilpercent1);
  Blynk.virtualWrite(V7, Soilpercent2);
  digitalWrite(LEDpin, HIGH);
  delay(250);
  Serial.print("\nGarden 1 Humidity = ");
  Serial.println(h1);
  Serial.print("\nGarden 1 Temperature = ");
  Serial.println(t1);
  Serial.print("\nGarden 2 Humidity = ");
  Serial.println(h2);
  Serial.print("\nGarden 2 Temperature = ");
  Serial.println(t2);
  Serial.print("\nAVG Humidity = ");
  Serial.println(AVGh);
  Serial.print("\nAVG Temperature = ");
  Serial.println(AVGt);
  Serial.print("\nSoil Moisture Sensor1 = ");
  Serial.println(Soil1);
  Serial.print("\nSoil Moisture Sensor2 = ");
  Serial.println(Soil2);
  Serial.print("\nSoil AVG SoilGarden 1 = ");
  Serial.println(AVGSoilGarden1);
  Serial.print("\nSoilpercent Garden 1 = ");
  Serial.println(Soilpercent1);
  Serial.print("\nSoil Moisture Sensor3 = ");
  Serial.println(Soil3);
  Serial.print("\nSoil Moisture Sensor4 = ");
  Serial.println(Soil4);
  Serial.print("\nSoil AVG SoilGarden 2 = ");
  Serial.println(AVGSoilGarden2);
  Serial.print("\nSoilpercent Garden 2 = ");
  Serial.println(Soilpercent2);
  Serial.print("\nGarden 1 Adjust Temp = ");
  Serial.println(AdjustTemp1);
  Serial.print("\nGarden 2 Adjust Temp = ");
  Serial.println(AdjustTemp2);
  Serial.print("\nGarden 1 Adjust Humidity = ");
  Serial.println(AdjustHumidity1);
  Serial.print("\nGarden 2 Adjust Humidity = ");
  Serial.println(AdjustHumidity2);
  Serial.print("\nGarden 1 Adjust Soil Moisture = ");
  Serial.println(AdjustSoil1);
  Serial.print("\nGarden 2 Adjust Soil Moisture = ");
  Serial.println(AdjustSoil2);

  if (AVGSoilGarden1 <= AdjustSoil1)
  {
    delay(10);
    if (15 <= AVGSoilGarden1 <= AdjustSoil1)
    {
      WaterGarden1();
    }
  }
  if (AVGSoilGarden2 <= AdjustSoil2)
  {
    delay(10);
    if (15 <= AVGSoilGarden2 <= AdjustSoil2)
    {
      WaterGarden2();
    }
  }
  if (AVGh <= AdjustHumidity1)
  {
    delay(10);
    if (AVGh <= AdjustHumidity1)
    {
      SprayHumidity();
    }
      }
  if (AVGt >= AdjustTemp1)
  {
    delay(10);
    if (AVGt >= AdjustTemp1)
    {
      SprayTemp();
    }
  }
  if (AVGh <= AdjustHumidity2)
  {
    delay(10);
    if (AVGh <= AdjustHumidity2)
    {
      SprayHumidity();
    }
  }
  if (AVGt >= AdjustTemp2)
  {
    delay(10);
    if (AVGt >= AdjustTemp2)
    {
      SprayTemp();
    }
  }
  //Safety

  /*
  if (AVGSoilGarden1 >= AdjustSoil1)
  {
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
  }
  if (AVGSoilGarden2 >= AdjustSoil2)
  {
    Blynk.virtualWrite(V14, 0);
  }
  if (AVGh >= AdjustHumidity1 || AVGh >= AdjustHumidity2 || AVGt >= AdjustTemp1 || AVGt >= AdjustTemp2)
  {
    Blynk.virtualWrite(V3, 0);
  }
  */

  digitalWrite(LEDpin, LOW);
  delay(250);
}
