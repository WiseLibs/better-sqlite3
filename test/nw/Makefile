NODE_WEBKIT_VERSION=0.8.4

all: app.nw

node_modules/sqlite3:
	npm install https://github.com/mapbox/node-sqlite3/tarball/master --build-from-source --runtime=node-webkit --target_arch=ia32 --target=$(NODE_WEBKIT_VERSION)

rebuild:
	cd node_modules/sqlite3 && ./node_modules/.bin/node-pre-gyp rebuild --runtime=node-webkit --target_arch=ia32 --target=$(NODE_WEBKIT_VERSION)

node-webkit-v$(NODE_WEBKIT_VERSION)-osx-ia32.zip:
	wget https://s3.amazonaws.com/node-webkit/v$(NODE_WEBKIT_VERSION)/node-webkit-v$(NODE_WEBKIT_VERSION)-osx-ia32.zip

./node-webkit.app: node-webkit-v$(NODE_WEBKIT_VERSION)-osx-ia32.zip
	unzip -o node-webkit-v$(NODE_WEBKIT_VERSION)-osx-ia32.zip

app.nw: ./node-webkit.app Makefile package.json index.html node_modules/sqlite3
	zip app.nw index.html package.json node_modules

test: ./node-webkit.app app.nw
	./node-webkit.app/Contents/MacOS/node-webkit app.nw

package: ./node-webkit.app Makefile package.json index.html node_modules/sqlite3
	rm -rf node-sqlite-test.app
	cp -r ./node-webkit.app node-sqlite-test.app
	mkdir ./node-sqlite-test.app/Contents/Resources/app.nw/
	cp package.json ./node-sqlite-test.app/Contents/Resources/app.nw/
	cp index.html ./node-sqlite-test.app/Contents/Resources/app.nw/
	cp -r node_modules/ ./node-sqlite-test.app/Contents/Resources/app.nw/
	./node-sqlite-test.app/Contents/MacOS/node-webkit

clean:
	rm -rf ./node_modules/sqlite3
	rm -f ./app.nw
	rm -rf node-sqlite-test.app
	rm -f credits.html
	rm -f nwsnapshot

.PHONY: test
