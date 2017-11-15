#line 2 "BufferPrinter.ino"


#include <ArduinoUnit.h>
#include <BufferPrinter.h>


test(printer_errors)
{
    const size_t bufferSize = 2;
    uint8_t buffer[bufferSize];

    BufferPrinter printer(buffer, bufferSize);
    printer.println("Hello World");
    assertEqual(printer.getWriteError(), BufferPrinter::ERROR_OUT_OF_MEMORY);
}



void setup()
{
  Serial.begin(9600);
  while(!Serial) {;}
}

void loop()
{
  Test::run();
}
