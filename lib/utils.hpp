using Byte = unsigned char;

template <class T>
inline std::array<float, 3> get_float(T begin_point, T end_point) { // fix this part
    unsigned int index { 0 };
    std::array<float, 3> arr;
    for (auto it = begin_point; it != end_point; it += 4) {
        arr[index++] = *(reinterpret_cast<float*>(it));
    }
    return arr;
}

