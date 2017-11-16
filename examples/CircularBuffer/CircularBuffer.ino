//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <CircularBuffer.h>


const size_t bufferSize = 10;
uint8_t buffer[bufferSize];


void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();

    CircularBuffer circle(buffer, bufferSize);

    for (size_t i = 0; i < bufferSize + 1; ++i)
    {
        Serial.print("Put ");
        Serial.print(i);
        Serial.print(" ");
        Serial.println(circle.put(i));
    }

    for (size_t i = 0; i < bufferSize + 1; ++i)
    {
        uint8_t value = 0;

        Serial.print("Get ");
        Serial.print(circle.get(value));
        Serial.print(" Value = ");
        Serial.println(value);
    }

    Serial.print("Put ");
    Serial.print(254);
    Serial.print(" ");
    Serial.println(circle.put(254));

    uint8_t value = 0;

    Serial.print("Get ");
    Serial.print(circle.get(value));
    Serial.print(" Value = ");
    Serial.println(value);


}


void loop()
{
    delay(1000);
}