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


class BufferWriter
{
public:
    BufferWriter(uint8_t* data, size_t size, size_t offset = 0);

    template <typename Type>
    size_t write(const Type& data);

    template <typename Type>
    size_t write(const Type* data, size_t size);

    void setOffset(size_t offset);
    size_t getOffset() const;

    size_t size() const;

    size_t remaining() const;

private:
    BufferWriter(const BufferWriter& that);
    BufferWriter& operator = (const BufferWriter& that);

    size_t _write(const void* source, size_t size);

    uint8_t* _data;

    const size_t _size;

    size_t _offset;

};


template <typename Type>
size_t BufferWriter::write(const Type& data)
{
    return _write(&data, sizeof(Type));
}


template <typename Type>
size_t BufferWriter::write(const Type* data, size_t size)
{
    return _write(data, sizeof(Type) * size);
}