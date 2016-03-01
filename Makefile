all: build

build:
	node-gyp rebuild

clean:
	rm -rf build
