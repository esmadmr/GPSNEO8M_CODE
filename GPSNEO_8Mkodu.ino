#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 15, TXPin = 14; //UART HABERLEŞMESİ İSTERSEN I2C DE KULLANABİLİRSİN.
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  Serial3.begin(GPSBaud);

  Serial.println(F("GPS MODÜLÜ DENEMESİ"));
  Serial.println(F("TinyGPS Kütüphanesi ile DENEME"));
  Serial.print(F("Testing TinyGPS++ ")); Serial.println(TinyGPSPlus::libraryVersion());
  
  Serial.println();
}

void loop()
{
 
  while (Serial3.available() > 0)
    if (gps.encode(Serial3.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("GPS BULUNAMADI. LÜTFEN BAĞLANTI HATTINIZI KONTROL EDİNİZ."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("KONUM BİLGİSİ :   ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("BULUNMADI!"));
  }

  Serial.print(F("  TARİH / ZAMAN : "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("BULUNAMADI!"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("BULUNAMADI!"));
  }

  Serial.println();  }
