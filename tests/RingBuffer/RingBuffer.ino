#line 2 "BufferWriter.ino"

#include <ArduinoUnit.h>
#include <RingBuffer.h>

const size_t bufferSize = 10;
uint8_t buffer[bufferSize];

test(ring_buffer_errors)
{
    RingBuffer ring(buffer, bufferSize);

    uint8_t b = 0;
    assertEqual(ring.get(b), RingBuffer::STATUS_UNDERFLOW);


    for (size_t i = 0; i < bufferSize; ++i)
    {
        assertEqual(ring.put(i), RingBuffer::STATUS_OK);
    }

    assertEqual(ring.put(0), RingBuffer::STATUS_OVERFLOW);
}


test(ring_buffer_errors_2)
{
    RingBuffer ring(buffer, 0);
    uint8_t b = 0;
    assertEqual(ring.get(b), RingBuffer::STATUS_INVALID);
    assertEqual(ring.put(b), RingBuffer::STATUS_INVALID);
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
