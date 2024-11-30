#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void mainStation(int16_t x);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 1 second

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  static int16_t x = 41; // Initial x position
  static bool moving = false; // Flag to check if it's moving

  if (!moving) {
    mainStation(x); // Call the function to display at position x
    delay(3000); // Start stationary for 2 seconds
    moving = true; // Start moving
  }

  if (x >= -45) {
    mainStation(x); // Call the function to display at position x
    x--; // Move to the left
    delay(80); // Change position every 200 milliseconds
  } else {
    delay(300); // Stop for 300 milliseconds
    mainStation(200); // Call the function to display text outside of screen ... so the text disappears
    delay(500); // Wait for 500 milliseconds
    x = 41; // Reset x position
    moving = false; // Reset moving flag
  }
}

void mainStation(int16_t x) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(x, 13);
  display.setTextWrap(false);
  display.println(F("Hlavna stanica"));

  display.fillRect(0, 0, 40, 32, SSD1306_BLACK);
  display.setCursor(1, 9);
  display.setTextSize(3);
  display.println(F("71"));


  display.display();
}