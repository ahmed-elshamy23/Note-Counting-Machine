#include "app.h"

#define ROWS 4
#define COLS 4

#define startCountingMachine 0xFF

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
static byte rowPins[ROWS] = {2, 3, 4, 5};
static byte colPins[COLS] = {6, 7, 8, 9};
static char keys[ROWS][COLS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'c', '0', '=', '+'}};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

static byte lcdRowCursorPosition = 0, correctPasswordFlag = 1, inputPasswordLength = 0;
char password[6] = {'1', '2', '3', '4', '5', '6'}; // the password is 123456

void appInit()
{
    lcd.begin(20, 4);
    lcd.print("Enter pass & =");
    Serial.begin(9600);
}

byte acceptInputFromKeypad()
{
    lcd.setCursor(lcdRowCursorPosition, 1);
    return keypad.getKey();
}

byte verifyPassword(byte key)
{
    if (key)
    {
        if (key == '=')
        {
            if (correctPasswordFlag == 0 || inputPasswordLength != 6)
            {
                lcd.clear();
                lcd.print("wrong pass");
                delay(2000);
                lcd.clear();
                lcd.print("try again");
                delay(2000);
                lcd.clear();
                lcd.print("Enter pass & =");
                inputPasswordLength = 0;
                correctPasswordFlag = 1;
                lcdRowCursorPosition = 0;
                return WRONG_PASSWORD;
            }
            else
            {
                lcd.clear();
                lcd.print("True");
                delay(2000);
                lcd.clear();
                lcd.print("welcome <3");
                delay(2000);
                return CORRECT_PASSWORD;
            }
        }
        else
        {
            lcd.print("*");
            if (key != password[lcdRowCursorPosition])
            {
                correctPasswordFlag = 0;
            }
            else
            {
                correctPasswordFlag = 1;
            }
            if (lcdRowCursorPosition == 20)
            {
                lcdRowCursorPosition = 0;
            }
            ++lcdRowCursorPosition;
            ++inputPasswordLength;
        }
    }
    return STILL_VERIFYING;
}

void sendUartFrame(byte data)
{
    Serial.write(startCountingMachine);
}

void startCounting()
{
    sendUartFrame(startCountingMachine);
    lcd.clear();
    lcd.print("Waiting for input...");
}

void printAmountOfMoney()
{
    unsigned short int moneyAmount;
    Serial.end();
    Serial.begin(9600);
    do
    {
        moneyAmount = Serial.read();
    } while (moneyAmount == 65535);
    lcd.clear();
    lcd.print("Amount = ");
    lcd.print(moneyAmount);
    lcd.print(" EGP");
}