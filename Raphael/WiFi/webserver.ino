/*! Author: Raphael Nepomuceno <raphael@nepomuceno.dev> */

#include <Adafruit_NeoPixel.h>

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define LED_PIN (A0)

#define ROWS (1)
#define COLS (8)

#define SSID ("Arc")
#define PASS ("4/6/6/2/20")

// WiFi {{{

void connect() {
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    Serial.println("Waiting to connect...");
    delay(500);
  }

  Serial.println(WiFi.localIP());
}
// }}}

// LED helper {{{

Adafruit_NeoPixel pixels =
    Adafruit_NeoPixel(ROWS * COLS, LED_PIN, NEO_GRB + NEO_KHZ800);

/// Sets up the LED strip.
void leds_begin() { pixels.begin(); }

/// Sends the updates to the LED strip.
void leds_flush() { pixels.show(); }

/// Lights up a pixel.
void leds_pixel(int x, int y, int r, int g, int b) {
  // Odd rows are counted backwartds.
  if (y % 2 == 1)
    x = (COLS - 1) - x;

  pixels.setPixelColor(COLS * y + x, pixels.Color(r, g, b));
}
// }}}

// Web server {{{

ESP8266WebServer server(80);

void httpd_begin() {
  server.on("/", httpd_handle_index);
  server.on("/update", httpd_handle_update);

  server.begin();
  Serial.println("Server listening");
}

void httpd_update() {
  // HTTP server tick.
  server.handleClient();
}

void httpd_handle_index() {
  // Reply.
  server.send(200, "text/html", "<!DOCTYPE html><html xmlns=\"http://www.w3.org/1999/xhtml\"> <head> <meta charset=\"utf-8\"/> <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"/> <title>Startpage</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/> <link rel=\"stylesheet\" href=\"https://cdn.rawgit.com/necolas/normalize.css/8.0.0/normalize.css\"/> <link rel=\"stylesheet\" href=\"https://cdn.rawgit.com/milligram/milligram/v1.3.0/dist/milligram.min.css\"/> <link rel=\"stylesheet\" href=\"https://raw.githack.com/cacauvicosa/inf351_2019/master/Raphael/WiFi/site.css\"/> </head> <body> <input type=\"color\" id=\"picker\" value=\"#ff0000\"/> <div id=\"grid\"></div><script src=\"https://cdn.rawgit.com/WebReflection/hyperHTML/v2.13.0/min.js\"></script> <script src=\"https://raw.githack.com/cacauvicosa/inf351_2019/master/Raphael/WiFi/site.js\"></script> </body></html>")
}

void httpd_handle_update() {
  int x = server.arg("x").toInt();
  int y = server.arg("y").toInt();
  int r = server.arg("r").toInt();
  int g = server.arg("g").toInt();
  int b = server.arg("b").toInt();

  leds_pixel(x, y, r, g, b);
  leds_flush();

  server.send(200, "text/plain", "Ok!");
}
// }}}

void setup() {
  Serial.begin(115200);

  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  leds_begin();

  connect();
  httpd_begin();
}

void loop() { httpd_update(); }
