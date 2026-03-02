#include <iostream>
#include <omp.h>
#include <thread>
using namespace std;

int main() {
    cout << "========================================\n";
    cout << "   PDC Assignment: Hardware Discovery   \n";
    cout << "========================================\n\n";

    // 1. Threading Capabilities
    cout << "--- Threading & Core Info ---\n";
    
    // Total logical threads available to the system
    unsigned int logical_threads = thread::hardware_concurrency();
    cout << "Logical Hardware Threads: " << logical_threads << "\n";
    
    // Max OpenMP threads configured currently
    int omp_max_threads = omp_get_max_threads();
    cout << "Max OpenMP Threads Available: " << omp_max_threads << "\n\n";

    // 2. SIMD Capabilities (GCC/Clang specific built-ins)
    cout << "--- SIMD Architecture Support ---\n";

    if (__builtin_cpu_supports("sse4.2")) {
        cout << "[YES] SSE4.2: Supported (128-bit registers, 4x32-bit floats)\n";
    } else {
        cout << "[NO]  SSE4.2: Not Supported\n";
    }
    
    // Check for AVX (Advanced Vector Extensions - 256 bit)
    if (__builtin_cpu_supports("avx")) {
        cout << "[YES] AVX Supported\n";
    } else {
        cout << "[NO]  AVX Not Supported\n";
    }

    // Check for AVX2 (Integer support for 256 bit)
    if (__builtin_cpu_supports("avx2")) {
        cout << "[YES] AVX2 Supported\n";
        cout << "      -> SIMD Register Width: 256 bits\n";
        cout << "      -> Single-precision (32-bit) lanes: 8\n";
        cout << "      -> Double-precision (64-bit) lanes: 4\n";
    } else {
        cout << "[NO]  AVX2 Not Supported\n";
    }

    // Check for AVX-512 (512 bit)
    if (__builtin_cpu_supports("avx512f")) {
        cout << "[YES] AVX-512 Supported\n";
    } else {
        cout << "[NO]  AVX-512 Not Supported\n";
    }

    cout << "\n========================================\n";
    return 0;
}