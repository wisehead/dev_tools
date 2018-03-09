# $Id: Makefile,v 1.9 2007/08/07 13:22:37 huqu Exp $
# Description: Makefile of Pending pool, epoll version.
#
# $Author: huqu $
# Copyright (c) 2007 by Baidu.com, Incorporation, P.R.C
# All rights reserved.
#
#

# Parameter
TARGET = cacheclear
PUBLISH = ./output/
VERSION = 1.0.0.0

# Source files
SRCS = clear.cpp
HEADS = $(wildcard *.h)

# Object files
OBJS = $(SRCS:.cpp=.o)

# C compiler options
#
CC=g++

ifeq ($(MAC), 64)
	VERSION := $(VERSION)_64bit
	ULIB = ../../../../lib2-64
	KERNEL = 26
else
	VERSION := $(VERSION)_32bit
	ULIB = ../../../../lib2
	KERNEL = 24
endif

DEFINES = -DVERSION="\"$(VERSION)\"" -DKERNEL=$(KERNEL)
INC = -I.
CPPFLAGS = -g -finline-functions -W -Wall -Winline -pipe -O2
LDFLAGS = 


# Debug or not
ifeq "$(MAKECMDGOALS)" "release"
	DEFINES += -DNDEBUG
endif
ifeq "$(MAKECMDGOALS)" "debug"
	DEFINES += -DDEBUG
	VERSION += debug
endif
ifeq "$(MAKECMDGOALS)" "demo"
	DEFINES += -DDEMO
endif

.cpp.o :
	$(CC) -c $(CPPFLAGS) $(INC) $(DEFINES) $<
	@echo

all : deps tags $(TARGET) $(PUBLISH)

# Make target
$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)
	@echo

$(PUBLISH) : $(TARGET)
	@if [ -d $@ ]; then rm -rf $@; fi
	@mkdir $@;
	cp $^ $@;
	@echo;

demo : $(OBJS)
	$(CC) -o $@ $^ $(CPPFLAGS) $(INC) $(DEFINES) -lpthread
# Depends
deps : $(SRCS) $(HEADS)
	@$(CC) -MM -MG $(CPPFLAGS) $(INC) $(DEFINES) $(filter %.c %.cpp, $^) > $@

# Make ctags
tags : $(SRCS) $(HEADS)
	@ctags $^

# Clean
clean :
	rm -rf $(TARGET) *.o *~ .\#*.cpp* .\#*.h* .\#Makefile.*
veryclean : clean
	rm -rf deps tags $(PUBLISH)

# Clean and make all
rebuild : clean all

# Make release version
release : rebuild

# Make debug version
debug : rebuild

.PHONY : clean veryclean all rebuild release debug

-include deps

