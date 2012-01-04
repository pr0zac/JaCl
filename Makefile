HOSTNAME = $(shell hostname -s)
ARCH = $(shell uname -m)

ifeq ($(ARCH), x86_64)
NACL_ARCH = amd64
else
NACL_ARCH = x86
endif

INCLUDES+=-I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers -I./NaCl/build/$(HOSTNAME)/include/$(NACL_ARCH)
LDFLAGS+=-L./NaCl/build/$(HOSTNAME)/lib/$(NACL_ARCH) -lnacl -arch $(ARCH)

CFLAGS+=$(INCLUDES)
CXXFLAGS=$(CFLAGS)

all: libjacl.jnilib
libjacl.jnilib: JaCl.class JaCl.h nacl.dylib NaClInterface.o
	g++ $(INCLUDES) -c JaCl.cpp -o JaCl.o
	g++ $(LDFLAGS) -dynamiclib -o libjacl.jnilib JaCl.o NaClInterface.o ./NaCl/build/$(HOSTNAME)/lib/$(NACL_ARCH)/randombytes.o
JaCl.h: JaCl.class
	javah -jni JaCl
JaCl.class: JaCl.java
	javac JaCl.java
nacl.dylib:
	#echo "Building NaCl library. This may take a while..."
	#cd NaCl; ./do
clean:
	rm *.o JaCl.h libjacl.jnilib JaCl.class
