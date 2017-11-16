#line 2 "BufferReader.ino"

#include <ArduinoUnit.h>
#include <BufferReader.h>
#include <BufferWriter.h>

const size_t bufferSize = 10;
uint8_t buffer[bufferSize];

test(sizes)
{
    BufferWriter writer(buffer, bufferSize);

    for (size_t i = 0; i < bufferSize; ++i)
    {
        size_t n = writer.write(uint8_t(i));
        assertEqual(n, sizeof(uint8_t));
    }

    BufferReader reader(buffer, bufferSize);

    for (size_t i = 0; i < bufferSize; ++i)
    {
        uint8_t b;
        size_t nRead = reader.read(b);
        assertEqual(nRead, sizeof(uint8_t));
        assertEqual(b, uint8_t(i));
    }

    reader.setOffset(0);

    // Serial.print("Array ");

    for (size_t i = 0; i < bufferSize; ++i)
    {
        Serial.print(buffer[i]);
        Serial.print(",");
    }

    // Serial.println("");

    for (uint8_t i = 0; i < bufferSize; i+=2)
    {
        uint16_t w;
        size_t nRead = reader.read(w);
        assertEqual(nRead, sizeof(uint16_t));
        reader.setOffset(reader.getOffset() - nRead);
        uint8_t l;
        uint8_t h;

        reader.read(l); // The high byte comes first in little endian.
        reader.read(h); // The low byte comes second in little endian.

        assertEqual(word(h, l), w);
    }

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
