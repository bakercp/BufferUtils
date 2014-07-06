// =============================================================================
//
// Copyright (c) 2013-2014 Christopher Baker <http://christopherbaker.net>
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


class DataView
{
public:
    enum ByteOrder
    {
        BIG_ENDIAN_BYTE_ORDER,
		LITTLE_ENDIAN_BYTE_ORDER
    };

    DataView(uint8_t* data, size_t size);
        
    ~DataView();

    size_t set(const uint8_t* data, size_t size);

    size_t write(uint8_t data);
    size_t write(uint16_t data);
    size_t write(uint32_t data);
    size_t write(uint64_t data);

    size_t write(int8_t data);
    size_t write(int16_t data);
    size_t write(int32_t data);
    size_t write(int64_t data);

    size_t write(const uint8_t* data, size_t size);
    size_t write(const uint16_t* data, size_t size);
    size_t write(const uint32_t* data, size_t size);
    size_t write(const uint64_t* data, size_t size);

    size_t write(const int8_t* data, size_t size);
    size_t write(const int16_t* data, size_t size);
    size_t write(const int32_t* data, size_t size);
    size_t write(const int64_t* data, size_t size);

    bool readUInt8(uint8_t& value) const;
    bool readUInt16(uint16_t& value) const;
    bool readUInt32(uint32_t& value) const;
    bool readUInt64(uint64_t& value) const;

    bool readInt8(int8_t& value) const;
    bool readInt16(int16_t& value) const;
    bool readInt32(int32_t& value) const;
    bool readInt64(int64_t& value) const;

    bool readUInt8(uint8_t* destination, size_t size) const;
    bool readUInt16(uint16_t* destination, size_t size) const;
    bool readUInt32(uint32_t* destination, size_t size) const;
    bool readUInt64(uint64_t* destination, size_t size) const;

    bool readInt8(int8_t* destination, size_t size) const;
    bool readInt16(int16_t* destination, size_t size) const;
    bool readInt32(int32_t* destination, size_t size) const;
    bool readInt64(int64_t* destination, size_t size) const;

    const uint8_t& operator[](size_t index) const;

    const uint8_t* data() const;
    size_t capacity() const;
    size_t size() const;
    size_t index() const;

    bool empty() const;
    bool full() const;

    void rewind() const;
    void clear();

    ByteOrder byteOrder() const;

private:
    DataView(const DataView& that);
    DataView& operator = (const DataView& that);

    size_t _write(const void* source, size_t size);
    size_t _read(void* destination, size_t size) const;

    uint8_t* _data;

    size_t _capacity;
    size_t _size;

    mutable size_t _index;

};
