#line 2 "BufferWriter.ino"

#include <ArduinoUnit.h>
#include <BufferWriter.h>

const size_t bufferSize = 10;
uint8_t buffer[bufferSize];

test(writer_remaining)
{
    BufferWriter writer(buffer, bufferSize);
    assertEqual(writer.remaining(), bufferSize);
}

test(writer_remaining_2)
{
    BufferWriter writer(buffer, bufferSize, -bufferSize);
    assertEqual(writer.remaining(), 0);
}

test(writer_remaining_3)
{
    BufferWriter writer(buffer, bufferSize, bufferSize * bufferSize);
    assertEqual(writer.remaining(), 0);
}


test(init)
{
    BufferWriter writer(buffer, bufferSize);
    assertEqual(writer.size(), bufferSize);
    assertEqual(writer.remaining(), bufferSize);
    assertEqual(writer.getOffset(), 0);
}


test(fill_buffer)
{
    BufferWriter writer(buffer, bufferSize);
    size_t s0 = writer.write(uint8_t(255));
    assertEqual(s0, sizeof(uint8_t));
    assertEqual(writer.remaining(), bufferSize - s0);

    size_t s1 = writer.write(uint16_t(255));
    assertEqual(s1, sizeof(uint16_t));
    assertEqual(writer.remaining(), bufferSize - s0 - s1);

    size_t s2 = writer.write(uint32_t(255));
    assertEqual(s2, sizeof(uint32_t));
    assertEqual(writer.remaining(), bufferSize - s0 - s1 - s2);

    uint8_t bytes[3] = { 0, 1, 2 };
    size_t s3 = writer.write(bytes, 3);
    assertEqual(s3, sizeof(uint8_t) * 3);
    assertEqual(writer.remaining(), bufferSize - s0 - s1 - s2 - s3);

    // Full!
    size_t s4 = writer.write(uint8_t(0));
    assertEqual(s4, 0);

    writer.setOffset(bufferSize - 1);
    assertEqual(writer.remaining(), 1);

    size_t s5 = writer.write(uint8_t(0));
    assertEqual(s5, 1);
    assertEqual(writer.remaining(), 0);
}

test(fill_struct)
{
    // This struct is packed by design.
    struct {
        uint16_t a;
        uint16_t b;
        uint16_t c;
        uint16_t d;
        uint8_t e;
        bool f;
    } myStruct;

    Serial.print("Struct size: ");
    Serial.println(sizeof(myStruct));

    BufferWriter writer(buffer, bufferSize);
    size_t s0 = writer.write(myStruct);
    assertEqual(s0, sizeof(myStruct));
    assertEqual(writer.remaining(), 0);

    // There shouldn't be anything left.
    size_t s1 = writer.write(myStruct);
    assertEqual(s1, 0);
    assertEqual(writer.remaining(), 0);

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
