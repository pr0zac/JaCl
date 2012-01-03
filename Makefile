all: libjacl.jnilib  
libjacl.jnilib: JaCl.class JaCl.h  
	gcc -dynamiclib -I/System/Library/Frameworks/JavaVM.framework/Versions/Current/Headers JaCl.c -o libjacl.jnilib -m64  
JaCl.h: JaCl.class  
	javah -jni JaCl  
JaCl.class: JaCl.java  
	javac JaCl.java  
clean:
	rm JaCl.h libjacl.jnilib JaCl.class
