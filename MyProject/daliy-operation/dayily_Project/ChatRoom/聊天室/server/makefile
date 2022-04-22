SSS:server.o reg.o log.o flag.o mod.o
	gcc server.o reg.o log.o flag.o mod.o -o SSS -lsqlite3 -lpthread
server.o:server.c myhead.h
reg.o:reg.c myhead.h
log.o:log.c myhead.h
flag.o:flag.c myhead.h
mod.o:mod.c myhead.h
clean:
	rm -rf *.o SSS *.db
