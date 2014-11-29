#include <Arduino.h>

void
setup(void)
{
    Serial.begin(38400);
    Serial.println("setup:");
}

void
loop(void)
{
    Serial.println("loop:");
    delay(1000);
}
