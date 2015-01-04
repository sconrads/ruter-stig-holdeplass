#include "rest_client.h"
#include "HttpClient.h"


#define HTTP_DEBUG

RestClient client = RestClient("reisapi.ruter.no");

HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    { "Accept" , "application/json"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t httpRequest;
http_response_t httpResponse;

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
  delay(5000);
  Serial.println("Setter igang...");

  IPAddress dnshost(ip_config.aucDNSServer[3], ip_config.aucDNSServer[2], ip_config.aucDNSServer[1], ip_config.aucDNSServer[0]);
  Serial.print(dnshost);

  IPAddress remoteIP(188,95,243,225);
  httpRequest.ip = remoteIP;
  httpRequest.port = 80;

  #ifdef HTTP_DEBUG
    Serial.println("I debug mode ja...");
  #endif

  httpRequest.path = "http://reisapi.ruter.no/stopvisit/getdepartures/3012072";

  http.get(httpRequest, httpResponse, headers);
  Serial.print("Application>\tResponse status: ");
  Serial.println(httpResponse.status);

  Serial.print("Application>\tHTTP Response Body: ");
  Serial.println(httpResponse.body);

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
