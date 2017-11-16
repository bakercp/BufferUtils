BufferUtils
===========

[![Build Status](https://travis-ci.org/bakercp/BufferUtils.svg?branch=master)](https://travis-ci.org/bakercp/BufferUtils)

## Description

An Arduino library to facilitate working with raw byte arrays.

## Features

- Javascript `DataView` style byte buffer access for reading (`BufferReader`) and writing (`BufferWriter`).
- A `Print` interface for a raw byte buffer via `BufferPrinter`
- A circular buffer (aka ring buffer or cyclic buffer) implementation for data arrays of any type in `CircularBuffer`.

## Background

When working with memory constrained systems, low-level communication protocols and other specialized code, it is very useful to be able to reduce everything down to an array of bytes, (aka byte buffers). Just about all quantitative data can be interpreted as arrays of bytes and this library will help you do that without too much complex C/C++ syntax.

## Use

### BufferReader

Say you have an array of bytes representing a communication packet with the form

```
PACKET TYPE uint16_t
PACKET LENGTH uint32_t
PACKET DATA variable array of uint8_t
CRC32 CHECKSUM uint32_t
```

One could read this data from the buffer like so:

```c++
uint8_t rawData[128] = { 0x00, 0x01, ..., 0x22 };

uint16_t packetType;
uint32_t packetLength;
uint8_t data[256];
uint32_t checksum;

BufferReader reader(rawData, 128);

// Fill packetType with the correct value.
reader.read(packetType);

// Fill packet length with the correct value.
reader.read(packetLength);

// Fill the data with the correct data using the variable packet length.
reader.read(data, packetLength);

// Fill the checksum.
reader.read(checksum);

```

The `BufferReader` keeps track of the current read position based on the sizes of the data types read. Each `read` operation returns the number of bytes read, or zero if there is a read error (e.g. running out of buffer to read).  Note the above example doesn't have any error checking.

### BufferWriter

Similarly, if we want to write a packet like that described above we might do the following:

```c++
uint8_t sendBuffer[128];

uint16_t packetType = 13;
uint32_t packetLength = 11;
uint8_t data[11] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd' };
uint32_t checksum = 0x4A17B156;

BufferWriter writer(sendBuffer, 128);

// Write the packetType to the send buffer.
writer.write(packetType);

// Write the packetLength to the send buffer.
writer.write(packetLength);

// Write the data to the send buffer.
reader.read(data, packetLength);

// Write the checksum.
reader.read(checksum);

// Send the data that was written to the buffer.
Serial.write(sendBuffer, reader.getOffset());
```

### BufferPrinter

`BufferPrinter` is much like `BufferWriter` but implements the Arduino `Print` interface.

```c++
uint8_t bufferToFill[128];

BufferPrinter printer(bufferToFill, 128);

// Write the packetType to the send buffer.
printer.println("Hello there.");

// All Print commands are available.
printer.print(".");

// Print commands including ASCII translations.
printer.print(99, HEX);

// Send the data that was written to the buffer.
Serial.write(bufferToFill, printer.getOffset());
```

### CircularBuffer

See the `CircularBuffer` example.

## Examples

See the included examples and tests for further usage examples.

## Changelog
See [CHANGELOG.md](CHANGELOG.md)


## License
See [LICENSE.md](LICENSE.md)