UBPF_DIR = ../ubpf
UBPF_LIB = $(UBPF_DIR)/ubpf.so

CC     = gcc
CFLAGS = -std=c11 -fPIC -Wall -g -I$(UBPF_DIR)
LDFLAGS= -Wl,-rpath,/ -l:ubpf.so
TARGET = test.so
SRC    = test.c

.PHONY: all clean module 

all: $(UBPF_LIB) $(TARGET)

$(UBPF_LIB):
	$(MAKE) -C $(UBPF_DIR)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(UBPF_DIR) $(LDFLAGS)

module: $(TARGET) #  $(UBPF_LIB) add this if you dont use .require in module.py

clean:
	rm -f $(TARGET)
	$(MAKE) -C $(UBPF_DIR) clean
