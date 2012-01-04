HOSTNAME = $(shell hostname -s)
ARCH = $(shell uname -m)

ifeq ($(ARCH), x86_64)
NACL_ARCH = amd64
else
NACL_ARCH = x86
endif

all: libjacl.jnilib
libjacl.jnilib: JaCl.class JaCl.h nacl.dylib
	gcc -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers -I./NaCl/build/$(HOSTNAME)/include/$(NACL_ARCH) -c JaCl.c -o JaCl.o
	gcc -dynamiclib -L./NaCl/build/$(HOSTNAME)/lib/$(NACL_ARCH) -lnacl -o libjacl.jnilib JaCl.o
JaCl.h: JaCl.class
	javah -jni JaCl
JaCl.class: JaCl.java
	javac JaCl.java
nacl.dylib:
	#echo "Building NaCl library. This may take a while..."
	#cd NaCl; ./do
clean:
	rm JaCl.o JaCl.h libjacl.jnilib JaCl.class
