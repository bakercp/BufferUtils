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


template <typename Type>
class RingBuffer_
{
public:
    enum Status
    {
        OK = 0,
        OVERFLOW,
        UNDERFLOW
    };


    RingBuffer_(Type* data, size_t size):
        _data(data),
        _size(size),
        _head(0),
        _count(0)
    {
    }


    Status put(const Type& data)
    {
        size_t tail = (_head + _count) % _size;

        _data[tail] = data;

        if (_count == _size)
        {
            _head = (_head + 1) % _size;
            return OVERFLOW;
        }
        else
        {
            ++_count;
            return OK;
        }
    }


    Status get(Type& data)
    {
        if (_count == 0)
        {
            return UNDERFLOW;
        }
        else
        {
            data = _data[_head];
            _head = (_head + 1) % _size;
            --_count;
            return OK;
        }
    }


    size_t count() const
    {
        return _count;
    }


    size_t size() const
    {
        return _size;
    }


    bool full() const
    {
        return _count == _size;
    }


    bool empty() const
    {
        return _count == 0;
    }


    void clear()
    {
        _head = 0;
        _count = 0;
    }

private:
    // RingBuffer_(const RingBuffer_& that);
    // RingBuffer_& operator = (const RingBuffer_& that);

    // A pointer to the backing byte buffer.
    Type* _data;

    /// \brief The size of the buffer.
    const size_t _size;

    /// \brief The head is the index at which the buffer begins.
    size_t _head;

    /// \brief The count of the buffer.
    size_t _count;

};


typedef RingBuffer_<uint8_t> RingBuffer;
