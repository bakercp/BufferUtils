//
// Copyright (c) 2013 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Arduino.h"


/// \brief A class for writing various types to a raw data byte buffer.
///
/// This is somewhat similar to a DataView in Javascript.
///
/// \sa https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/DataView
class BufferWriter
{
public:
    /// \brief Create a BufferWriter from the given data.
    /// \param data A pointer to the data buffer to write to.
    /// \param size The number of bytes in the data buffer.
    /// \param offset The offset to begin writing.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    BufferWriter(uint8_t* data, size_t size, size_t offset = 0);

    /// \brief Write a data value to the data buffer.
    /// \tparam Type The data type to read.
    /// \param value The value to write.
    /// \returns The numbner of bytes written. On success, the return value will
    ///          be equal to `sizeof(Type)`. On failure, the number of bytes
    ///          read will be zero.
    template <typename Type>
    size_t write(const Type& value);

    /// \brief Write an array of data values to the data buffer.
    /// \tparam Type The data type to write.
    /// \param valueArray The array to write.
    /// \param size The number of bytes in the value array.
    /// \returns The numbner of bytes written. On success, the return value will
    ///          be equal to `sizeof(Type) * size`. On failure, the number of
    ///          bytes written will be zero.
    template <typename Type>
    size_t write(const Type* valueArray, size_t size);

    /// \brief Set the write offset to the given position.
    /// \param offset The read offset position within the byte buffer.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    void setOffset(size_t offset);

    /// \brief Move the read position ahead \p offset number of bytes.
    /// \param offset The number of bytes to move the write position ahead.
    void skip(size_t offset);

    /// \brief Get the current write position of the offset.
    ///
    /// After writing is complete, this represents the length of the filled
    /// buffer.
    ///
    /// \returns the current write position offset.
    size_t getOffset() const;

    /// \returns the size of the byte buffer provided during construction.
    size_t size() const;

    /// \returns size() - getOffset(), where getOffset() is always <= size().
    size_t remaining() const;

private:
    BufferWriter(const BufferWriter& rhs);
    BufferWriter& operator = (const BufferWriter& rhs);

    /// \brief Utility function to write an arbitrary data type.
    /// \param source The source to copy values from.
    /// \param size The number of bytes in the source.
    /// \returns the number of bytes writtern.
    size_t _write(const void* source, size_t size);

    /// \brief A pointer to the data buffer.
    uint8_t* _data = nullptr;

    /// \brief The size of the _data buffer.
    const size_t _size = 0;

    /// \brief The current offset of the writer.
    size_t _offset = 0;

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
