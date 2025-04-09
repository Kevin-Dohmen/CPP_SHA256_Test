#ifndef BINOPS_H
#define BINOPS_H

#include <cstddef> // for size_t
#include <type_traits> // For std::is_unsigned

class BinOps {
public:
    BinOps() = delete;

    template<typename T>
    static constexpr T rotl(T value, size_t shift){
        static_assert(std::is_unsigned<T>::value, "Rotation only valid for unsigned types");
        constexpr size_t width = sizeof(T) * 8;
        shift &= (width - 1); // mod
        if (shift == 0) return value;
        return (value << shift) | (value >> (width - shift));
    }

    template<typename T>
    static constexpr T rotr(T value, size_t shift){
        static_assert(std::is_unsigned<T>::value, "Rotation only valid for unsigned types");
        constexpr size_t width = sizeof(T) * 8;
        shift &= (width - 1); // mod
        if (shift == 0) return value;
        return (value >> shift) | (value << (width - shift));
    }
};

#endif // BINOPS_H