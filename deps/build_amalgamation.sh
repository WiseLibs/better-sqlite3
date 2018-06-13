#!/bin/sh
# Download fossil + sqlite repository, and builds the amalgamation with
# SQLITE_ENABLE_UPDATE_DELETE_LIMIT defined. fossil and the repository are
# cached to speed future downloads
set -e

deps_dir=$(dirname -- "$(readlink -e "$0")")
sqlite_fossil_cache=$HOME/.cache/sqlite3-fossil-repository
mkdir -pv $sqlite_fossil_cache
fossil="$sqlite_fossil_cache/fossil"
repo="$sqlite_fossil_cache/sqlite.fossil"
if [ ! -x $fossil ]; then
	# download fossil
	curl https://www.fossil-scm.org/fossil/uv/fossil-linux-x64-2.5.tar.gz | \
		tar xfz - -C $sqlite_fossil_cache
fi
if [ ! -e "$repo" ]; then
	# clone/checkout sqlite
	$fossil clone https://www.sqlite.org/src $repo
else
	$fossil pull https://www.sqlite.org/src -R $repo
fi
checkout_dir=$(mktemp -d)
cd $checkout_dir
$fossil open $repo version-3.22.0
# generate amalgamation
./configure --enable-update-limit
make sqlite3.c
tar cvzf $deps_dir/sqlite3-amalg.tar.gz sqlite3.c sqlite3.h sqlite3ext.h
cd -
rm -rf $checkout_dir
