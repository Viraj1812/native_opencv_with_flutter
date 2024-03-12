#include <stdint.h>
#include <vector>

// Exporting functions for FFI
#if defined _WIN32
    #define FFI_PLUGIN_EXPORT __declspec(dllexport)
#else
    #define FFI_PLUGIN_EXPORT
#endif

#if _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

FFI_PLUGIN_EXPORT intptr_t sum(intptr_t a, intptr_t b);
FFI_PLUGIN_EXPORT intptr_t multiply(intptr_t a, intptr_t b);
FFI_PLUGIN_EXPORT uint64_t factorial(uint64_t n);
FFI_PLUGIN_EXPORT intptr_t manipulate_matrix();
FFI_PLUGIN_EXPORT intptr_t sum_long_running(intptr_t a, intptr_t b);

#ifdef __cplusplus
}
#endif
