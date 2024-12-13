
.PHONY: unit run buildrun watch shutdown

# CXX = clang++
CXXFLAGS = -std=c++20 -I.. -Wall -Wextra -pthread

# Conditionally define PREFIX only for macOS (Darwin)
ifneq ($(OS), Windows_NT)
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Darwin)
        PREFIX ?= $(shell brew --prefix)
	endif
endif

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
	$(CXX) -o ../bin/cryptor $(CXXFLAGS) cryptor.cpp $(OPENSSL_SUPPORT) $(ZLIB_SUPPORT) $(BROTLI_SUPPORT) -I../include

unit:
	$(CXX) -o ../bin/unit $(CXXFLAGS) unit.cpp $(OPENSSL_SUPPORT) $(ZLIB_SUPPORT) $(BROTLI_SUPPORT) -I../include

clean:
	rm bin/*

page:
	curl -k https://localhost:2022/

pages:
	clear
	echo "local..."
	curl -k https://localhost:2022/ | head -10
	echo "alamo..."
	curl -k https://alamo:2022/ | head -10
	echo "peidmont..."
	curl -k https://piedmont:2022/ | head -10
	echo "tiburon..."
	curl -k https://tiburon.local:2022/ | head -10

shutdown:
	curl -k -XDELETE https://localhost:2022/shutdown

shutdown_all:
	clear
	echo "shutting down all..."
	curl -k -XDELETE https://localhost:2022/shutdown
	curl -k -XDELETE https://alamo:2022/shutdown
	curl -k -XDELETE https://piedmont:2022/shutdown
	curl -k -XDELETE https://tiburon.local:2022/shutdown

watch:
	watchexec --debounce 500 --clear --postpone  --watch ../server --exts cpp,hpp,yaml make unit
