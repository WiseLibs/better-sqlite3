void Statement::CloseHandles::operator() (Statement* stmt) {
	delete stmt->handles;
	stmt->handles = NULL;
}
