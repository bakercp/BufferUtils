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

    while (writer.remaining())
    {
        Serial.print("Offset: ");
        Serial.print(writer.getOffset());

        uint8_t value = writer.remaining();

        size_t size = writer.write(value);

        Serial.print(" Bytes Written: ");
        Serial.print(size);
        Serial.print(" Value: ");
        Serial.print(value);
        Serial.print(" Offset: ");
        Serial.print(writer.getOffset());
        Serial.println();
    }

    BufferReader reader(buffer, bufferSize);

    while (reader.remaining())
    {
        uint16_t value;

        Serial.print("Offset: ");
        Serial.print(reader.getOffset());
        Serial.print(" Value: ");

        if (reader.read(value))
        {
            Serial.print(value);
        }
        else
        {
            Serial.print("Error");
            break;
        }

        Serial.print(" Offset: ");
        Serial.print(reader.getOffset());

        Serial.println();
    }
}


void loop()
{

}