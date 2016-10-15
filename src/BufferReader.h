// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "Arduino.h"


class BufferReader
{
public:
    BufferReader(const uint8_t* data, size_t size, size_t offset = 0);

    template <typename Type>
    size_t read(Type& value) const;

    template <typename Type>
    size_t read(Type* destination, size_t size) const;

    void setOffset(size_t offset);

    void skip(size_t offset);

    size_t getOffset() const;

    size_t size() const;

    size_t remaining() const;

private:
    BufferReader(const BufferReader& that);
    BufferReader& operator = (const BufferReader& that);

    size_t _read(void* destination, size_t size) const;

    const uint8_t* _data;

    const size_t _size;

    mutable size_t _offset;

};


template <typename Type>
size_t BufferReader::read(Type& value) const
{
    return _read(&value, sizeof(Type));
}


template <typename Type>
size_t BufferReader::read(Type* destination, size_t size) const
{
    return _read(destination, sizeof(Type) * size);
}
