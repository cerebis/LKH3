all:
	make -C SRC
clean:
	make -C SRC clean
	/bin/rm -f *~ ._*