#ifndef UBPF_H
#define UBPF_H

#ifdef __cplusplus
extern "C" {
#endif


// Declare the optional runtime entrypoint
int ubpf_runtime(int argc, char** argv);

#ifdef __cplusplus
}
#endif

#endif // UBPF_H
