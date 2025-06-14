static void (*bpf_print)(char *) = (void *)1;
int entry(void* ctx) {
    // call your helper; any args get passed through, we ignore them
    char msg[] = "Hello from eBPF!";
    bpf_print(&msg[0]);
    return 42;
}