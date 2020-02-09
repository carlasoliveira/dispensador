#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// set the LCD number of columns and rows
int lcdColumns = 20;
int lcdRows = 4;

LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

const byte ROWS = 4; // number of rows of the keypad
const byte COLS = 4; // number of columns of the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'/', '0', ':', 'D'}
};

byte rowPins[ROWS] = {27, 14, 12, 13}; // row pinouts of the keypad R1 = D27, R2 = D14, R3 = D12, R4 = D13
byte colPins[COLS] = {32, 33, 26, 25};    // column pinouts of the keypad C1 = D32, C2 = D33, C3 = D26, C4 = D25

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(115200);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
}
int col = 0;
void loop() {
  char key = keypad.getKey();
  // set cursor to first column, first row
  lcd.setCursor(col, 0);
  if (key != NO_KEY) {
    Serial.println(key);
    // print message
    lcd.print(key);
    delay(50);
    col = col + 1;
  }
  if (key == 'C') {
    lcd.clear();
    col = 0;
  }
  if (key == 'D') {
    lcd.clear();
    lcd.print("Ok!");
    delay(1000);
    lcd.clear();
    col = 0;
  }
  if (key == 'B') {
    lcd.clear();
    lcd.print("Remedio armazenado");
    delay(1000);
    lcd.clear();
    col = 0;
  }
}
