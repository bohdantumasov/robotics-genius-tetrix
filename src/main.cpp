#include <Arduino.h>
#include <PRIZM_PRO.h>

PRIZM prizm;

void setup()
{
  // Ініціалізація контролера й очікування зеленої кнопки Start
  prizm.PrizmBegin();
}

void loop()
{
  prizm.setRedLED(HIGH);
  delay(500);

  prizm.setRedLED(LOW);
  delay(500);
}