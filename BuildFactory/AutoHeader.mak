##
## yabasic BeOS Makefile
## Part for BuildFactory
##

##
## enable debug
##
# DBG = -g 

##
## enable optimization
##
OPT = -O

##
## Libraries
##
LIBPATH = -L/boot/home/config/lib
LIB = -lncurses -lbe -lroot -ltranslation 

## flags for flex (-d for debugging)
FLEXFLAGS = -i -I -L -s

## flags for bison (-t -v for debugging)
BISONFLAGS = -d -l -t -v  

