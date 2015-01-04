#include "rest_client.h"

RestClient client = RestClient("reisapi.ruter.no");

int led = D7; // This one is the built-in tiny one to the right of the USB jack
int ekstraLed = D0;
String response;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starter...");
    pinMode(led, OUTPUT);
    pinMode(ekstraLed, OUTPUT);
    digitalWrite(led, LOW);
    digitalWrite(ekstraLed, LOW);
}
void loop()
{

  IPAddress dnshost(ip_config.aucDNSServer[3], ip_config.aucDNSServer[2], ip_config.aucDNSServer[1], ip_config.aucDNSServer[0]);
  Serial.print(dnshost);

  response = "";
  int statusCode = client.get("/stopvisit/getdepartures/3012072", &response);
  //int statusCode = client.get("/Heartbeat/Index", &response);
  //int statusCode = client.get("/get", &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(3000);
}
