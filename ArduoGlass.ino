#include <U8x8lib.h>          // Include the U8x8 library
#include <SoftwareSerial.h>   // Include the Software Serial library for the Bluetooth module

// OLED Pins
#define OLED_CLK 13
#define OLED_DIN 11
#define OLED_CS 10
#define OLED_DC 9
#define OLED_RES 8

// Bluetooth module pins
#define BT_RX 2
#define BT_TX 3

U8X8_SH1106_128X64_WINSTAR_4W_SW_SPI display (OLED_CLK, OLED_DIN, OLED_CS, OLED_DC, OLED_RES); // Setting up the OLED with the OLED Pins
SoftwareSerial mySerial =  SoftwareSerial(BT_RX, BT_TX);                                       // Setting up the Bluetooth serial with the Bluetooth module Pins

String data; // Variable to store the buffer coming from the Bluetooth module serial connection

void setup() {
  display.begin(); // Starting the display
  display.setFont(u8x8_font_chroma48medium8_r); // Setting the font
  display.clear();                              // Clearing the display
  mySerial.begin(9600);                         // Starting the Bluetooth module serial connection
  display.print("This OLED is ready!");         // Display startup message
}

void loop() {
  while(mySerial.available()) {   // Checking availability of the Bluetooth module serial connection
    char c = mySerial.read();     // Getting character buffer from the Bluetooth module serial
    if (c != -1) {
      data += c;                  // Store the characters from the character buffer into the data string
      if (c == '\n') {            // Detecting the end of line
        display.clear();          // Clear the display
        display.print(data);      // Show the data string on the display
        data = "";                // Clear the data string
        break;
      }
    }
  }
}
