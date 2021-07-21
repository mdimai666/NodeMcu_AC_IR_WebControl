#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <WiFiClient.h>

const char *ssid = "";
const char *password = "";
MDNSResponder mdns;

ESP8266WebServer server(80);

#define pult_on 0xB2BFC0
#define pult_off 0xB27BE0

IRsend irsend(4);

uint16_t a_on[199] = {4370, 4462, 504, 1650, 506, 570, 530, 1626, 506, 1650, 506, 570, 506, 570, 506, 1650, 504, 572, 506, 570, 506, 1650, 530, 548, 530, 548, 506, 1648, 530, 1626, 506, 570, 506, 1648, 506, 1650, 506, 572, 504, 1650, 506, 1648, 530, 1626, 508, 1648, 508, 1648, 506, 1648, 506, 570, 506, 1672, 500, 554, 506, 572, 506, 572, 506, 572, 504, 572, 506, 572, 506, 570, 506, 1650, 506, 570, 508, 1648, 506, 570, 530, 546, 506, 572, 506, 570, 506, 1648, 506, 572, 506, 1650, 504, 572, 506, 1648, 506, 1648, 508, 1648, 504, 1650, 506, 5250, 4372, 4462, 506, 1648, 504, 572, 506, 1648, 506, 1650, 506, 572, 530, 546, 506, 1650, 504, 572, 506, 572, 530, 1624, 506, 572, 504, 572, 506, 1648, 506, 1648, 506, 572, 506, 1650, 530, 1624, 506, 570, 506, 1650, 530, 1624, 506, 1648, 530, 1624, 508, 1648, 506, 1648, 506, 570, 508, 1648, 506, 570, 506, 570, 506, 572, 510, 566, 506, 572, 504, 572, 506, 572, 506, 1650, 504, 572, 504, 1650, 506, 572, 506, 570, 506, 572, 506, 572, 508, 1648, 506, 570, 506, 1648, 506, 570, 506, 1648, 506, 1650, 504, 1652, 504, 1648, 506};	// COOLIX B2BF50
uint16_t a_off[199] = {4398, 4434, 534, 1622, 532, 544, 534, 1622, 534, 1622, 534, 542, 534, 544, 532, 1620, 534, 542, 534, 544, 532, 1624, 532, 544, 532, 546, 532, 1622, 532, 1622, 532, 544, 534, 1622, 536, 542, 532, 1622, 534, 1622, 534, 1622, 534, 1622, 532, 544, 532, 1622, 536, 1622, 532, 1622, 532, 544, 532, 546, 532, 544, 532, 544, 534, 1620, 532, 544, 532, 544, 534, 1620, 534, 1622, 532, 1622, 532, 544, 532, 546, 532, 544, 532, 544, 532, 546, 534, 542, 532, 544, 534, 542, 534, 1620, 534, 1620, 534, 1620, 534, 1624, 532, 1622, 532, 5222, 4400, 4434, 532, 1620, 534, 544, 532, 1622, 532, 1622, 532, 544, 532, 544, 534, 1620, 534, 546, 532, 544, 532, 1622, 534, 542, 534, 544, 534, 1622, 532, 1620, 534, 544, 534, 1620, 532, 546, 532, 1622, 534, 1622, 534, 1620, 534, 1622, 532, 544, 534, 1620, 534, 1620, 532, 1622, 534, 544, 532, 546, 532, 544, 532, 546, 530, 1622, 534, 544, 532, 544, 532, 1624, 532, 1620, 534, 1622, 532, 544, 530, 546, 532, 544, 534, 544, 532, 546, 530, 544, 532, 544, 532, 546, 534, 1620, 532, 1620, 534, 1622, 532, 1624, 532, 1620, 532}; // COOLIX B27BE0

void setup()
{
	irsend.begin();
	Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

	WiFi.begin(ssid, password);
	Serial.println("");

	while (!Serial){;}

	Serial.println("Kentatsu AC init\n");

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (mdns.begin("esp8266", WiFi.localIP()))
	{
		Serial.println("MDNS responder started");
	}

	server.on("/", handleRoot);
	server.on("/ir", handleIr);

	server.on("/inline", []()
			  { server.send(200, "text/plain", "this works as well"); });

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{

	// if (0)
	// { //work
	// int khz = 38; // несущая частота 38kHz для протокола NEC
	//   irsend.sendRaw(a_on, sizeof(a_on) / sizeof(a_on[0]), khz);
	//   delay(2000);
	//   irsend.sendRaw(a_off, sizeof(a_off) / sizeof(a_off[0]), khz);
	//   delay(2000);
	// }

	// if (1) //work
	// {
	//   irsend.sendCOOLIX(0xB2BF50);
	//   delay(2000);
	//   irsend.sendCOOLIX(0xB27BE0);
	//   delay(2000);
	// }
	server.handleClient();
}

void handleRoot()
{
	server.send(200, "text/html",
				"<html>"
				"<head><title>ESP8266 Demo</title></head>"
				"<body>"
				"<h1>Hello from ESP8266, you can send NEC encoded IR"
				"signals from here!</h1>"
				"<p><a href=\"ir?code=on\">ON</a></p>"
				"<p><a href=\"ir?code=off\">OFF</a></p>"
				"<p><a href=\"ir?code=11714496\">Send 0xB2BF50</a></p>"
				"</body>"
				"</html>");
}

void handleIr()
{
	for (uint8_t i = 0; i < server.args(); i++)
	{
		if (server.argName(i) == "code")
		{
			String val = server.arg(i);

			if(val == "on"){
				irsend.sendCOOLIX(pult_on);
			} else if(val == "off"){
				irsend.sendCOOLIX(pult_off);
			} else {
			    uint32_t code = strtoul(val.c_str(), NULL, 10);
				irsend.sendCOOLIX(code);
			}

		}
	}
	handleRoot();
}

void handleNotFound()
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++)
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	server.send(404, "text/plain", message);
}