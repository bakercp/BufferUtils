//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Arduino.h"


/// \brief A class for reading various types from a raw data byte buffer.
///
/// This is somewhat similar to a DataView in Javascript.
///
/// \sa https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView
class BufferReader
{
public:
    /// \brief Create a BufferReader from the given data.
    /// \param data A pointer to the data buffer to read from.
    /// \param size The number of bytes in the data buffer.
    /// \param offset The offset to begin reading.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    BufferReader(const uint8_t* data, size_t size, size_t offset = 0);

    /// \brief Read a data value from the data buffer.
    /// \tparam Type The data type to read.
    /// \param value The value to fill.
    /// \returns The numbner of bytes read. On success, the return value will
    ///          be equal to `sizeof(Type)`. On failure, the number of bytes
    ///          read will be zero.
    template <typename Type>
    size_t read(Type& value) const;

    /// \brief Read an array of data values from the data buffer.
    /// \tparam Type The data type to read.
    /// \param valueArray The array to fill.
    /// \param size Size of the array to fill.
    /// \returns The numbner of bytes read. On success, the return value will
    ///          be equal to `sizeof(Type) * size`. On failure, the number of
    ///          bytes read will be zero.
    /// \warning This function assumes that destination has at least `size`
    ///          bytes allocated.
    template <typename Type>
    size_t read(Type* valueArray, size_t size) const;

    /// \brief Set the read offset to the given position.
    /// \param offset The read offset position within the byte buffer.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    void setOffset(size_t offset);

    /// \brief Move the read position ahead \p offset number of bytes.
    /// \param offset The number of bytes to move the read position ahead.
    void skip(size_t offset);

    /// \returns the current read position offset.
    size_t getOffset() const;

    /// \returns the size of the byte buffer provided during construction.
    size_t size() const;

    /// \returns size() - getOffset(), where getOffset() is always <= size().
    size_t remaining() const;

private:
    BufferReader(const BufferReader& rhs);
    BufferReader& operator = (const BufferReader& rhs);

    /// \brief Utility function to read an arbitrary data type.
    /// \param destination The destination to copy values into.
    /// \param size The number of bytes in the destination.
    /// \returns the number of bytes read.
    size_t _read(void* destination, size_t size) const;

    /// \brief A pointer to the data buffer.
    const uint8_t* _data = nullptr;

    /// \brief The size of the _data buffer.
    const size_t _size = 0;

    /// \brief The current offset of the reader.
    mutable size_t _offset = 0;

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
