GMPFLAGS=-lgmpxx -lgmp
CFLAGS=-combine -o
SRCS=main.cpp nt_funcs.cpp vec.cpp llist.cpp common.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

enc: $(SRCS)
	g++ $(CFLAGS) enc $(SRCS) $(GMPFLAGS)
	
clean:
	rm -f $(OBJS)