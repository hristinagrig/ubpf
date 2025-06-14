#include <stdio.h>
#include "../ubpf/ubpf_runtime.h"

// Declare the uBPF runtime entrypoint as a weak symbol.
// This prevents a link‐time error when ubpf_runtime() isn't yet defined.
extern int ubpf_runtime(int argc, char** argv) __attribute__((weak));

int main(int argc, char** argv) {
 printf("Hello from test application\n");
    if (ubpf_runtime) {
        int ret = ubpf_runtime(argc, argv);
        printf("ubpf_runtime returned: %d\n", ret);
    } else {
        printf("ubpf_runtime not available\n");
    }

    return 0;
}
