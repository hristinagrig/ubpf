CC  = gcc
BPF_CC  = clang

INCLUDES = -Ivm -Ivm/inc -Ivm/build

CFLAGS   = -std=c11 -fPIC -g -Wall $(INCLUDES)
BPF_CFLAGS = -O2 -target bpf \

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

prog.o: prog.c 
	$(BPF_CC) $(BPF_CFLAGS) -c $< -o $@

ubpf.so: ubpf_runtime.o vm/ubpf_vm.o vm/ubpf_loader.o vm/ubpf_instruction_valid.o ubpf_helpers.o vm/ubpf_jit.o vm/ubpf_jit_x86_64.o vm/ubpf_jit_support.o
	$(CC) $(CFLAGS) -shared -o $@ $^

# OSv module target
module: ubpf.so prog.o

clean:
	rm -f vm/*.o ubpf.so prog.o
