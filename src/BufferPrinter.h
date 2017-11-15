//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Arduino.h"
#include "BufferWriter.h"


/// \brief A class for printing into a raw data byte buffer.
///
/// Implements the Arduino Print interface. Is similar to a BufferWriter.
///
/// \sa BufferWriter
/// \sa https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.h
/// \sa https://www.arduino.cc/en/Serial/Print
class BufferPrinter: public Print
{
public:
    /// \brief Create a BufferPrinter from the given data.
    /// \param data A pointer to the data buffer to write to.
    /// \param size The number of bytes in the data buffer.
    /// \param offset The offset to begin writing.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    BufferPrinter(uint8_t* data, size_t size, size_t offset = 0);

    /// \brief Write a data value to the data buffer.
    /// \tparam Type The data type to read.
    /// \param value The value to write.
    /// \returns The numbner of bytes written. On success, returns 1.
    size_t write(uint8_t value) override;

    /// \brief Write an array of data values to the data buffer.
    /// \tparam Type The data type to write.
    /// \param valueArray The array to write.
    /// \param size The number of bytes in the value array.
    /// \returns The numbner of bytes written. On success, the return value will
    ///          be equal to `size`. On failure, the number of bytes written
    ///          will be zero.
    size_t write(const uint8_t* valueArray, size_t size) override;

    /// \returns the number of bytes that can be written without blocking.
    int availableForWrite();

    /// \brief Set the write offset to the given position.
    /// \param offset The read offset position within the byte buffer.
    /// \note If offset is set to a value greater than size(), it will be set to size().
    void setOffset(size_t offset);

    /// \brief Move the read position ahead \p offset number of bytes.
    /// \param offset The number of bytes to move the write position ahead.
    void skip(size_t offset);

    /// \returns the current read position offset.
    size_t getOffset() const;

    /// \returns the size of the byte buffer provided during construction.
    size_t size() const;

    /// \returns size() - getOffset(), where getOffset() is always <= size().
    size_t remaining() const;

    /// \brief An error that is set if the write operation will exceed the size of the wrapped buffer.
    enum
    {
        ERROR_OUT_OF_MEMORY = 2
    };

private:
    BufferPrinter(const BufferPrinter& rhs);
    BufferPrinter& operator = (const BufferPrinter& rhs);

    /// \brief The BufferWriter we write into.
    mutable BufferWriter _bufferWriter;

};
