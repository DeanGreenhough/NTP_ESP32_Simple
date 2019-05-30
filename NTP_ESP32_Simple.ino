/*
 Author: Dean Greenhough 2019
 NTP TEST FOR DISPLAY - lastUpdated
 */

#include <WiFi.h>
#include "time.h"
#include "credentials.h"
//NTP
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec	   = 0;
const int   daylightOffset_sec = 3600;
String time_str; //GLOBAL TIME STRING

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");			//See http://www.cplusplus.com/reference/ctime/strftime/
  //See parameter listings 
  char output[80];
  strftime(output, 25, "%A %d %B %H:%M", &timeinfo);
  time_str = String(output);
  //Serial.print("time_str  ");
  Serial.println(time_str);										// Pass to display as update time
  Serial.print("");
  return;
  
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
