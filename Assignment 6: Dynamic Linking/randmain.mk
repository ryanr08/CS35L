randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) randmain.o randcpuid.o -o randmain

randmain.o: randmain.c randcpuid.h
	$(CC) $(CFLAGS) -c randmain.c

randcpuid.o: randcpuid.h
	$(CC) $(CFLAGS) -c randcpuid.c

randlibhw.o: randlib.h randlibhw.c
	$(CC) $(CFLAGS) -fPIC -c randlibhw.c

randlibsw.o: randlib.h randlibsw.c
	$(CC) $(CFLAGS) -fPIC -c randlibsw.c

randlibhw.so: randlibhw.o
	$(CC) $(CFLAGS) -shared randlibhw.o -o randlibhw.so

randlibsw.so: randlibsw.o
	$(CC) $(CFLAGS) -shared randlibsw.o -o randlibsw.so
