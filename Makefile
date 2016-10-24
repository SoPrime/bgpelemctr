all: bgp

bgp:
	gcc -o bgpelemctr bgpelemctr.c -lbgpstream
# use this syntax when having a custom bgpstream installation location
#	gcc -o bgpupdcnt bgpelemctr.c -L<custom lib/> -I<custom include/> -lbgpstream -Wl,-rpath=<custom lib/>
