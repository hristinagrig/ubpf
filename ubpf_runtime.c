#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ubpf.h"
#include "ubpf_runtime.h"
#include "ubpf_helpers.h"

/*
// This is your hook function
extern void ubpf_hook_print_hello(void) {
    printf("uBPF hook: hello from ubpf module!\n");
}

// This is the runtime entrypoint
extern int ubpf_runtime(int argc, char** argv) {
    printf("ubpf_runtime invoked with %d args\n", argc);
   // ubpf_hook_print_hello();
    return 0;
}
*/




static void register_helpers(struct ubpf_vm* vm) {
   ubpf_register(vm, 1, "bpf_print", (void*)bpf_print);
}

int ubpf_runtime(int argc, char** argv) {
    const char* filename = "/prog.o";

    // Load ELF file
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open ELF file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t elf_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    void* elf_data = malloc(elf_size);
    if (!elf_data || fread(elf_data, 1, elf_size, file) != elf_size) {
        perror("Failed to read ELF file");
        fclose(file);
        free(elf_data);
        return 1;
    }
    fclose(file);

    // Create uBPF VM
    struct ubpf_vm* vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create uBPF VM\n");
        free(elf_data);
        return 1;
    }

    // Load ELF and specify the entry function symbol name
    char* errmsg = NULL;
    const char* entry_name = "entry";
    register_helpers (vm);
    if (ubpf_load_elf_ex(vm, elf_data, elf_size, entry_name, &errmsg) < 0) {
        fprintf(stderr, "Failed to load ELF: %s\n", errmsg);
        free(errmsg);
        ubpf_destroy(vm);
        free(elf_data);
        return 1;
    }


    // Run the loaded program (entry point already resolved)
    /*
    uint64_t result = 0;
    if (ubpf_exec(vm, NULL, 0, &result) < 0) {
        fprintf(stderr, "Execution failed\n");
        ubpf_destroy(vm);
        free(elf_data);
        return 1;
    }
*/
    ubpf_jit_fn jitted_bpf = ubpf_compile(vm, &errmsg);
    if (!jitted_bpf) {
        fprintf(stderr, "JIT compile failed: %s\n", errmsg);
        free(errmsg);
        ubpf_destroy(vm);
        free(elf_data);
        return 1;
    }

    // Execute the JIT-compiled function
    uint64_t result = (jitted_bpf)(NULL, 0);
    printf("uBPF execution result: %lu\n", result);

    ubpf_destroy(vm);
    free(elf_data);
    return result;
}




int main(int argc, char** argv)  {
    printf("hello\n");
    ubpf_runtime(argc, argv);
    return 0;
}