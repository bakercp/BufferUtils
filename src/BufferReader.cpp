//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "BufferReader.h"


BufferReader::BufferReader(const uint8_t* data, size_t size, size_t offset):
    _data(data),
    _size(size),
    _offset(offset)
{
    if (_offset > _size)
        _offset = _size;
}


size_t BufferReader::_read(void* destination, size_t size) const
{
    if (_offset + size <= _size)
    {
        memcpy(destination, _data + _offset, size);
        _offset += size;
        return size;
    }
    else
    {
        return 0;
    }
}


void BufferReader::setOffset(size_t offset)
{
    if (offset <= _size)
        _offset = offset;
}


void BufferReader::skip(size_t offset)
{
    if (_offset + offset <= _size)
        _offset += offset;
}


size_t BufferReader::getOffset() const
{
    return _offset;
}


size_t BufferReader::size() const
{
    return _size;
}


size_t BufferReader::remaining() const
{
    return _size - _offset;
}
