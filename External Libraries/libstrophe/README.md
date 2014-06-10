# libstrophe #

libstrophe is a lightweight XMPP client library written in C. It has
minimal dependencies and is configurable for various environments. It
runs well on both Linux, Unix, and Windows based platforms.

Its goals are:

- usable quickly
- well documented
- reliable

## Build Instructions ##

An Xcode project which builds a dynamic library is provided.

A Visual Studio Project is forthcoming

### Examples ###

The `Examples` directory contains some examples of how to
use the library; these may be helpful in addition to the
API documentation

## Requirements ##

libstrophe requires:

- expat or libxml2
  - These are system libraries in OS X. The Xcode project defaults to libxml2
- libresolv on UNIX systems
  - This is a system library in OS X

In addition, if you wish to run the unit tests, you will need the
check package.

### OS X (with Homebrew package manager)

You can install the requirements with:

    brew install check

## Documentation

API documentation is inline with the code and conforms to Doxygen
standards. You can generate an HTML version of the API documentation
by running:

    doxygen

Then open `docs/html/index.html`.
