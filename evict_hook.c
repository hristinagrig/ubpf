

extern int print_hello(int);

int can_evict(void* buf) {
 //   print_hello(42);  // Call helper ID 1
 osv::debug("Hello from BPF: %lu\n", arg);
    return 0;         // Always say "don’t evict", but the C++ code will ignore it
}
