#include "CircularBuffer.h"
#include <algorithm>

CircularBuffer::CircularBuffer() : CircularBuffer(DEFAULT_SIZE) {}

CircularBuffer::CircularBuffer(size_type n) : elems{ new value_type[n] }, nelems{ 0 }, cap{ n }
{
    current = elems;
}

CircularBuffer::CircularBuffer(CircularBuffer& autre) : elems{ new value_type[autre.size()] }, nelems{ autre.size() }, cap{ autre.size() }
{
    std::copy(autre.begin(), autre.end(), begin());
}

[[nodiscard]] CircularBuffer::size_type CircularBuffer::size() const noexcept
{
    return nelems;
}

[[nodiscard]] CircularBuffer::size_type CircularBuffer::capacity() const noexcept
{
    return cap;
}

[[nodiscard]] CircularBuffer::iterator CircularBuffer::begin() const noexcept
{
    return elems;
}

[[nodiscard]] CircularBuffer::iterator CircularBuffer::end() const noexcept
{
    return begin() + size();
}

[[nodiscard]] CircularBuffer::iterator CircularBuffer::begin() noexcept
{
    return elems;
}

[[nodiscard]] CircularBuffer::iterator CircularBuffer::end() noexcept
{
    return begin() + size();
}

[[nodiscard]] CircularBuffer::value_type CircularBuffer::operator[](CircularBuffer::size_type n)
{
    return *(begin() + n);
}

[[nodiscard]] CircularBuffer::value_type CircularBuffer::operator[](CircularBuffer::size_type n) const
{
    return *(begin() + n);
}

[[nodiscard]] bool CircularBuffer::full() const noexcept
{
    return size() == capacity();
}

void CircularBuffer::add(CircularBuffer::value_type value) noexcept
{
    if (current == begin() + capacity())
    {
        current = begin();
    }
    *(current)++ = value;
    if (nelems < cap)
    {
        nelems++;
    }
}

CircularBuffer::~CircularBuffer()
{
    delete[] elems;
}
