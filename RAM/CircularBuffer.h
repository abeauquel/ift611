#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <cstddef>


class CircularBuffer
{
public:
    using pointer = unsigned long*;
    using value_type = unsigned long;
    using size_type = std::size_t;
    using iterator = pointer;

private:
    pointer elems{},
        current{};
    size_type  nelems{},
        cap{};
    const size_type DEFAULT_SIZE = 10;
public:
    CircularBuffer();
    CircularBuffer(size_type);
    CircularBuffer(CircularBuffer&);
    ~CircularBuffer();
    [[nodiscard]] size_type size() const noexcept;
    [[nodiscard]] size_type capacity() const noexcept;
    [[nodiscard]] iterator begin() const noexcept;
    [[nodiscard]] iterator end() const noexcept;
    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;
    [[nodiscard]] value_type operator[](size_type);
    [[nodiscard]] value_type operator[](size_type) const;
    void add(value_type) noexcept;

private:
    [[nodiscard]] bool full() const noexcept;

};

#endif // CIRCULARBUFFER_H
