//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <BufferReader.h>
#include <BufferWriter.h>


const size_t bufferSize = 10;
uint8_t buffer[bufferSize];


void setup()
{
    // Set the buffer to zero.
    memset(buffer, 0, sizeof(buffer));

    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();
    Serial.println();

    BufferWriter writer(buffer, bufferSize);

    Serial.println(writer.remaining() == bufferSize ? "PASS" : "FAIL");

    while (writer.remaining())
    {
        Serial.print("Remaining: ");
        Serial.print(writer.remaining());
        Serial.print(" Offset: ");
        Serial.print(writer.getOffset());

        uint8_t value = writer.remaining();
        value *= value;
        size_t size = writer.write(value);

        Serial.print(" Bytes Written: ");
        Serial.print(size);
        Serial.print(" ");
        Serial.print(size == sizeof(uint8_t) ? "PASS" : "FAIL");
        Serial.print(" Value: ");
        Serial.print(value);
        Serial.print(" Offset: ");
        Serial.print(writer.getOffset());
        Serial.println();
    }

    size_t size = writer.write(255);
    Serial.print("Fail-write: ");
    Serial.println(size == 0 ? "PASS" : "FAIL");

    Serial.print("Remaining: ");
    Serial.println(writer.remaining());

    writer.setOffset(bufferSize - 1);

    Serial.print("Remaining: ");
    Serial.println(writer.remaining());

    Serial.print("sizeof(255) = ");
    Serial.println(sizeof(255));

    size = writer.write(uint8_t(255));
    Serial.print(" ");
    Serial.print(size);
    Serial.print(" Success-write: ");
    Serial.println(size == sizeof(uint8_t) ? "PASS" : "FAIL");

    writer.setOffset(bufferSize - 1);
    size = writer.write(256);
    Serial.print("Fail-write: ");
    Serial.println(size == 0 ? "PASS" : "FAIL");

    Serial.print("Remaining: ");
    Serial.println(writer.remaining());

    BufferReader reader(buffer, bufferSize);

    Serial.println(reader.remaining() == bufferSize ? "PASS" : "FAIL");
}


void loop()
{
    delay(1000);
}