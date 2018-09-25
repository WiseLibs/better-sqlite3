#!/usr/bin/env sh

VERSION="3250100"
YEAR="2018"

echo "downloading source..."
DEPS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
TEMP="$DEPS/temp"
rm -rf "$TEMP"
mkdir -p "$TEMP"
curl -#f "https://www.sqlite.org/$YEAR/sqlite-src-$VERSION.zip" > "$TEMP/temp.zip" || exit 1
echo "extracting source..."
unzip "$TEMP/temp.zip" -d "$TEMP" > /dev/null || exit 1
cd "$TEMP/sqlite-src-$VERSION"

echo "configuring amalgamation..."
sh configure > /dev/null || exit 1

echo "building amalgamation..."
make sqlite3.c > /dev/null || exit 1

echo "generating tarball..."
tar czf "$DEPS/sqlite3.tar.gz" sqlite3.c sqlite3.h sqlite3ext.h || exit 1

echo "cleaning up..."
cd - > /dev/null
rm -rf "$TEMP"
MAJOR=`expr "${VERSION:0:1}" + 0`
MINOR=`expr "${VERSION:1:2}" + 0`
PATCH=`expr "${VERSION:3:2}" + 0`
sed -Eie "s/version [0-9]+\.[0-9]+\.[0-9]+/version $MAJOR.$MINOR.$PATCH/g" "$DEPS/../docs/compilation.md"
echo "done!"
