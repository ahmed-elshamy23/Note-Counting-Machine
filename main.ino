#include "app.h"

byte key, flag = 0;

void setup()
{
  appInit();
}

void loop()
{
  key = acceptInputFromKeypad();
  switch (verifyPassword(key))
  {
  case CORRECT_PASSWORD:
    flag++;
    startCounting();
  default:
    break;
  }
  if (flag)
  {
    printAmountOfMoney();
    while (1)
      ;
  }
}