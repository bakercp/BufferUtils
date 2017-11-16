# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased
### Fixed

## [3.0.0] 2017-11-15
### Fixed
- Compile errors on ESP8266 and Zero.

### Changed
- Changed `RingBuffer` to `CircularBuffer` in order to avoid name clashes with Arduino core.

## [2.0.0] 2017-11-14
### Added
- Changelog.
- `BufferPrinter` class for writing to a byte buffer with the `Print` interface.
- Tests
- Examples
- Documentation

### Changed
- Updated README.md, fixed errors, spelling and updated examples.
- Modified various functions to work with templates, but should be backward compatible.
