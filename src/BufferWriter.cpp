//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "BufferWriter.h"


BufferWriter::BufferWriter(uint8_t* data, size_t size, size_t offset):
    _data(data),
    _size(size),
    _offset(offset)
{
    if (_offset > _size)
        _offset = _size;
}


size_t BufferWriter::_write(const void* source, size_t size)
{
    if (_offset + size <= _size)
    {
        memcpy(_data + _offset, source, size);
        _offset += size;
        return size;
    }
    else
    {
        return 0;
    }
}


void BufferWriter::setOffset(size_t offset)
{
    if (offset <= _size)
        _offset = offset;
}


void BufferWriter::skip(size_t offset)
{
    if (_offset + offset <= _size)
        _offset += offset;
}


size_t BufferWriter::getOffset() const
{
    return _offset;
}


size_t BufferWriter::size() const
{
    return _size;
}


size_t BufferWriter::remaining() const
{
    return _size - _offset;
}
