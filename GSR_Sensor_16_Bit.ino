#include <Wire.h>
#include <Adafruit_ADS1X15.h>     //Bibliothek ADC ADS1115

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

int gsr_average = 0;              //Festlegung Variablen
int human_resistance = 0;
 
void setup(){
  Serial.begin(115200);
  ads.begin();

  //Verstärkung                                                    ADS1015  ADS1115
  //                                                               -------  -------
  //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV
  ads.setGain(GAIN_ONE);          // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV

  //Fehler bei Initialisierung ADC
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}
 
void loop(){
  int16_t adc0;
  float volts0;
  long sum = 0;
  
  for(int i=0; i<10; i++)                   //Mittelwertbildung über 10 Werte
      {
      adc0 = ads.readADC_SingleEnded(0);    //Auslesen der I2C-Kommunikation
      sum += adc0;                          //Summe der ausgelesenen Werte
      delay(5);
      }
   gsr_average = sum/10;                
   volts0 = ads.computeVolts(adc0);         //Auslesen der Spannung

   //Berechnung Hautwiderstand, 16-Bit -> andere Skalierung
   human_resistance = ((26184 + 2 * gsr_average) * 10000) / (13092 - gsr_average);

   //Ausgabe Messwerte
   //Serial.println("Rohwert (Spannung): ");     //Kalibrierung des GSR Sensors
   //Serial.println(gsr_average);
   Serial.println("Hautwiderstand in Ohm: ");
   Serial.println(human_resistance);
   //Serial.println("Spannung in V: ");
   //Serial.println(volts0);
   //Serial.println("\n");
}
