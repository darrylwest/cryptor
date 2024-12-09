# CXX = clang++
CXXFLAGS = -std=c++20 -I.. -Wall -Wextra -pthread

PREFIX ?= $(shell brew --prefix)

OPENSSL_DIR = $(PREFIX)/opt/openssl@3
OPENSSL_SUPPORT = -DCPPHTTPLIB_OPENSSL_SUPPORT -I$(OPENSSL_DIR)/include -L$(OPENSSL_DIR)/lib -lssl -lcrypto

ifneq ($(OS), Windows_NT)
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		OPENSSL_SUPPORT += -framework CoreFoundation -framework Security
	endif
endif

ZLIB_SUPPORT = -DCPPHTTPLIB_ZLIB_SUPPORT -lz

BROTLI_DIR = $(PREFIX)/opt/brotli
BROTLI_SUPPORT = -DCPPHTTPLIB_BROTLI_SUPPORT -I$(BROTLI_DIR)/include -L$(BROTLI_DIR)/lib -lbrotlicommon -lbrotlienc -lbrotlidec

all: cryptor

cryptor: cryptor.cpp
	$(CXX) -o cryptor $(CXXFLAGS) cryptor.cpp $(OPENSSL_SUPPORT) $(ZLIB_SUPPORT) $(BROTLI_SUPPORT)

run:
	./cryptor

clean:
	rm -f cryptor

watch:
	watchexec --debounce 500 --clear --postpone  --watch ../server --exts cpp,hpp,yaml make
