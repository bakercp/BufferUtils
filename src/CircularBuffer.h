//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Arduino.h"


/// \brief A templated class representing circular access to an array.
///
/// Circular buffers are also known as ring buffers or cyclic buffers.
///
/// \tparam Type The data type of the wrapped array.
/// \sa https://en.wikipedia.org/wiki/Circular_buffer
template <typename Type>
class CircularBuffer_
{
public:
    /// \brief The possible return status after get, put, and peek operations.
    enum Status
    {
        /// \brief The operation was successful.
        STATUS_OK = 0,
        /// \brief The head position overwrite the tail position.
        ///
        /// This might indicate possible data loss.
        STATUS_OVERFLOW,
        /// \brief A value was read, but there was no unread value available.
        ///
        /// This might indicate that the data read is invalid.
        STATUS_UNDERFLOW,
        /// \brief The operation was invalid, e.g. an empty data buffer.
        STATUS_INVALID
    };

    /// \brief Create a circular buffer from the given data.
    /// \param data A pointer to the data buffer to wrap.
    /// \param size The number of bytes in the data buffer.
    CircularBuffer_(Type* data, size_t size):
        _data(data),
        _size(size),
        _head(0),
        _count(0)
    {
    }

    /// \brief Insert data at the head position and advance the head position.
    ///
    /// If the underlying data is invalid or of size zero, STATUS_INVALID will
    /// be returned.
    ///
    /// If the head does not overtake the tail, STATUS_OK will be returned.
    /// If the head overtakes the tail, then STATUS_OVERFLOW will be returned,
    /// the tail will be incremented and overwritten by the head.
    ///
    /// \param data The data to put.
    /// \returns the status of the operation.
    Status put(const Type& data)
    {
        if (!_data || _size == 0)
            return STATUS_INVALID;

        size_t tail = (_head + _count) % _size;

        _data[tail] = data;

        if (_count == _size)
        {
            _head = (_head + 1) % _size;
            return STATUS_OVERFLOW;
        }
        else
        {
            ++_count;
            return STATUS_OK;
        }
    }

    /// \brief Get the data from the tail and advance the tail position.
    ///
    /// If the underlying data is invalid or of size zero, STATUS_INVALID will
    /// be returned.
    ///
    /// If the tail does not overtake the head, STATUS_OK will be returned.
    /// If the tail overtakes the head, then STATUS_UNDERFLOW will be returned,
    /// and neither the head or the tail will be incremented.
    ///
    /// \param data The data to put.
    /// \returns the status of the operation.
    Status get(Type& data)
    {
        if (!_data || _size == 0)
            return STATUS_INVALID;

        if (_count == 0)
        {
            return STATUS_UNDERFLOW;
        }
        else
        {
            data = _data[_head];
            _head = (_head + 1) % _size;
            --_count;
            return STATUS_OK;
        }
    }

    /// \brief Get the data from the tail but do not advance the tail position.
    ///
    /// If the underlying data is invalid or of size zero, STATUS_INVALID will
    /// be returned.
    ///
    /// If the tail does not overtake the head, STATUS_OK will be returned.
    /// If the tail overtakes the head, then STATUS_UNDERFLOW will be returned.
    ///
    /// \param data The data to put.
    /// \returns the status of the operation.
    Status peek(Type& data)
    {
        if (!_data || _size == 0)
            return STATUS_INVALID;

        if (_count == 0)
        {
            return STATUS_UNDERFLOW;
        }
        else
        {
            data = _data[_head];
            return STATUS_OK;
        }
    }

    /// \returns the nuber of items available in the circular buffer.
    size_t count() const
    {
        return _count;
    }

    /// \returns the total capacity of the circular buffer.
    size_t size() const
    {
        return _size;
    }

    /// \returns true if the count is equal to the size.
    bool full() const
    {
        return _count == _size;
    }

    /// \returns true if the count is zero.
    bool empty() const
    {
        return _count == 0;
    }

    /// \brief Effectively reset the circular buffer.
    ///
    /// The underlying data will not be zeroed, but the head and tail will be
    /// reset.
    void reset()
    {
        _head = 0;
        _count = 0;
    }

    /// \returns a read only pointer to the wrapped data.
    const Type* data() const
    {
        return _data;
    }

private:
    CircularBuffer_(const CircularBuffer_& that);
    CircularBuffer_& operator = (const CircularBuffer_& that);

    // A pointer to the backing byte buffer.
    Type* _data = nullptr;

    /// \brief The size of the buffer.
    const size_t _size = 0;

    /// \brief The head is the index at which the buffer begins.
    size_t _head = 0;

    /// \brief The count of the buffer.
    size_t _count = 0;

};

/// \brief A type definition for a standard 8-bit circular buffer.
typedef CircularBuffer_<uint8_t> CircularBuffer;
