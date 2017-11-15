//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "BufferPrinter.h"


BufferPrinter::BufferPrinter(uint8_t* data, size_t size, size_t offset):
    _bufferWriter(data, size, offset)
{
}


size_t BufferPrinter::write(uint8_t value)
{
    size_t result = _bufferWriter.write(value);

    if (result != sizeof(uint8_t))
        setWriteError(ERROR_OUT_OF_MEMORY);

    return result;
}


size_t BufferPrinter::write(const uint8_t* valueArray, size_t size)
{
    size_t result = _bufferWriter.write(valueArray, size);

    if (result != sizeof(uint8_t))
        setWriteError(ERROR_OUT_OF_MEMORY);

    return result;
}


int BufferPrinter::availableForWrite()
{
    return _bufferWriter.remaining();
}


void BufferPrinter::setOffset(size_t offset)
{
    _bufferWriter.setOffset(offset);
}


void BufferPrinter::skip(size_t offset)
{
    _bufferWriter.skip(offset);
}


size_t BufferPrinter::getOffset() const
{
    return _bufferWriter.getOffset();
}


size_t BufferPrinter::size() const
{
    return _bufferWriter.size();
}


size_t BufferPrinter::remaining() const
{
    return _bufferWriter.remaining();
}
