#ifndef APP_H
#define APP_H

#include <LiquidCrystal.h>
#include <Keypad.h>

#define CORRECT_PASSWORD 0
#define WRONG_PASSWORD 1
#define STILL_VERIFYING 2

void appInit();

byte acceptInputFromKeypad();

byte verifyPassword(byte key);

void sendUartFrame(byte data);

void startCounting();

void printAmountOfMoney();

#endif