//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <BufferPrinter.h>


const size_t bufferSize = 256;
uint8_t buffer[bufferSize];


void setup()
{
    Serial.begin(9600);
}


void loop()
{
    Serial.println(">");
    BufferPrinter printer(buffer, bufferSize);
    printer.println("Hello World!");    
    Serial.write(buffer, printer.getOffset());
    Serial.println("<");
    delay(1000);
}