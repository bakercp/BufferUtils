#line 2 "BufferWriter.ino"

#include <ArduinoUnit.h>
#include <CircularBuffer.h>


const size_t bufferSize = 10;
uint8_t buffer[bufferSize];

test(circular_buffer_errors)
{
    CircularBuffer circle(buffer, bufferSize);

    uint8_t b = 0;
    assertEqual(circle.get(b), CircularBuffer::STATUS_UNDERFLOW);


    for (size_t i = 0; i < bufferSize; ++i)
    {
        assertEqual(circle.put(i), CircularBuffer::STATUS_OK);
    }

    assertEqual(circle.put(0), CircularBuffer::STATUS_OVERFLOW);
}


test(circular_buffer_errors_2)
{
    CircularBuffer circle(buffer, 0);
    uint8_t b = 0;
    assertEqual(circle.get(b), CircularBuffer::STATUS_INVALID);
    assertEqual(circle.put(b), CircularBuffer::STATUS_INVALID);
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
