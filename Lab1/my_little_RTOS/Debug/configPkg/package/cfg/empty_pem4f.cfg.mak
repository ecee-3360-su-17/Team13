# invoke SourceDir generated makefile for empty.pem4f
empty.pem4f: .libraries,empty.pem4f
.libraries,empty.pem4f: package/cfg/empty_pem4f.xdl
	$(MAKE) -f /Users/yushen/Documents/GitHub/Team13/Lab1/my_little_RTOS/src/makefile.libs

clean::
	$(MAKE) -f /Users/yushen/Documents/GitHub/Team13/Lab1/my_little_RTOS/src/makefile.libs clean

