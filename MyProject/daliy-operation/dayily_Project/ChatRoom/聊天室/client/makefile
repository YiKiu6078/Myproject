CCC:client.o onechat.o allchat.o
	gcc client.o onechat.o allchat.o -o CCC -lsqlite3 -lpthread
client.o:client.c myhead.h
onechat.o:onechat.c myhead.h
allchat.o:allchat.c myhead.h
clean:
	rm -rf *.o SSS *.db
