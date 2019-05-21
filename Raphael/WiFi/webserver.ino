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
  server.send(200, "text/plain", "Hello world!");
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
