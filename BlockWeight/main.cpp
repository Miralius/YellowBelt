#include <iostream>

int main() {
    u_int32_t N;
    u_int16_t R;
    std::cin >> N >> R;
    u_int64_t totalWeight{};
    for (u_int32_t i = 0; i < N; ++i) {
        u_int16_t a;
        u_int16_t b;
        u_int16_t c;
        std::cin >> a >> b >> c;
        totalWeight += static_cast<u_int64_t>(a) * b * c * R;
    }
    std::cout << totalWeight;
    return 0;
}