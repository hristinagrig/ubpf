#include <stdio.h>
#include <stdint.h>
#include "ubpf_helpers.h"

/*
 * bpf_puts – a helper that takes a C‐string pointer from the eBPF program
 * and prints it to the host console.
 */
uint64_t bpf_print(char* a) {
    const char* buf = (const char*)a;
    if (!buf) return -1;
    printf("[eBPF] %s\n", buf);
    return 0;
}
