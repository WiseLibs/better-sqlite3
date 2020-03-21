#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

/*
	This SQLite3 extension is used only for testing purposes (npm test).

	This extension differs from the regular 'test_extension' as it defines
	a non-standard entry point.

	see: https://github.com/JoshuaWise/better-sqlite3/issues/363
 */

static void TestExtensionFunction(sqlite3_context* pCtx, int nVal, sqlite3_value** _) {
	sqlite3_result_double(pCtx, (double)nVal);
}

#ifdef _WIN32
__declspec(dllexport)
#endif

int custom_extension_init(sqlite3* db, char** pzErrMsg, const sqlite3_api_routines* pApi) {
	SQLITE_EXTENSION_INIT2(pApi)
	if (pzErrMsg != 0) *pzErrMsg = 0;
	sqlite3_create_function(db, "testExtensionFunction", -1, SQLITE_UTF8, 0, TestExtensionFunction, 0, 0);
	return SQLITE_OK;
}
