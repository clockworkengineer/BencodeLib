#pragma once
#include <cstddef>
namespace BencodeLib
{
    //
    // Interface for reading source stream during Bencode deocoding.
    //
    class ISource
    {
    public:
        virtual ~ISource() {}
        virtual char current() const = 0;
        virtual void next() = 0;
        virtual bool more() const = 0;
        virtual void reset() = 0;
    };
} // namespace BencodeLib