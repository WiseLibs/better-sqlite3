void Statement::DeleteHandles::operator() (Statement* stmt) {
	delete stmt->handles;
	stmt->handles = NULL;
}
