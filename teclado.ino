#include <Keypad.h>

const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {27, 14, 12, 13}; // row pinouts of the keypad R1 = D27, R2 = D14, R3 = D12, R4 = D13
byte colPins[COLS] = {32, 33, 26, 25};    // column pinouts of the keypad C1 = D32, C2 = D33, C3 = D26, C4 = D25

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println(key);
  }
}
