GMPFLAGS=-lgmpxx -lgmp
CFLAGS=-combine -o
SRCS=m.cpp funcs.cpp array.cpp llist.cpp common.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

enc: $(SRCS)
	g++ $(CFLAGS) enc $(SRCS) $(GMPFLAGS)
	
clean:
	rm -f $(OBJS)