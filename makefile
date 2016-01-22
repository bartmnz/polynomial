CFLAGS= -std=c11 -Wall -Werror -Wextra -pedantic -Wno-deprecated  -Wstack-usage=1024 

TARGET1=polynomial

OBJS1=polynomial.o 

.PHONY: clean debug profile python

$(TARGET1): $(OBJS1)

debug: CFLAGS+=-g
debug: $(TARGET1)


clean:
	-$(RM) $(TARGET1) $(OBJS1) 

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: $(TARGET)