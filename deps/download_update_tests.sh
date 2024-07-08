#!/usr/bin/env bash

set -e

# This file is meant to be called by deps/download.sh but has been broken out for easy testing.

# Script scoped variables
TESTS="$(CDPATH= cd -- "$(dirname -- "$0")/../test" && pwd)"
DEPS="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"

echo "updating tests ..."

# Getting variables from sqlite3 source code
echo "  getting values from sqlite3 code ..."
SQLITE_VARS="SQLITE_VERSION SQLITE_VERSION_NUMBER SQLITE_SOURCE_ID"
for SQLITE_VAR in $SQLITE_VARS; do
	echo "    getting $SQLITE_VAR from deps/sqlite3/sqlite3.c ..."
	# Matches lines like:
	#	#define SQLITE_VERSION        "3.44.2"
	MATCH_STRING="^#define[ \t]+${SQLITE_VAR}[ \t]+\"?([^\"]*)\"?"
	# Just print capture group of the value matched
	REPLACE_STRING="\1"
	# Dynamically initialize variable with given name to be the value
	# matched in the sqlite3.c file.
	declare $SQLITE_VAR="$(sed -n -E "s|$MATCH_STRING|$REPLACE_STRING|p" \
		"$DEPS/sqlite3/sqlite3.c")"
done

# Validate all need variables are populated
REQUIRED_VARS="$SQLITE_VARS"
MISSING_VARS=""
for REQUIRED_VAR in $REQUIRED_VARS; do
	if [ "${!REQUIRED_VAR}" = "" ]; then
		MISSING_VARS="$MISSING_VARS $REQUIRED_VAR"
	fi
done
if [ "$MISSING_VARS" != "" ]; then
	echo "ERROR! The following required env. vars. are not defined: $MISSING_VARS"
	exit 1
fi

# Do the file mutation
echo "  editing test files ..."
echo "    test/51.metadata.json ..."
for SQLITE_VAR in $SQLITE_VARS; do
	echo "      replacing $SQLITE_VAR with ${!SQLITE_VAR}"
	# Matches JSON lines like:
	#	"SQLITE_VERSION": "3.44.2",
	MATCH_STRING="\"$SQLITE_VAR\": (\"?)[^\",]*(\"?)(,?)$"
	REPLACE_STRING="\"$SQLITE_VAR\": \1${!SQLITE_VAR}\2\3"
	sed -E -i.bak \
		-e "s|$MATCH_STRING|$REPLACE_STRING|g" \
		"$TESTS/51.metadata.json"
done
