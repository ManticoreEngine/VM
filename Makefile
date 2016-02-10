j=2
make:
	cd Debug; make -j$(j)
	cp Debug/VM ./vm

clean:
	cd Debug; make clean
