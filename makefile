all:
	xmake
run:
	make all
	xmake run

clean:
	rm -rf build
	rm -rf .xmake