#ifndef BETTER_SQLITE3_FUNCTOR_H
#define BETTER_SQLITE3_FUNCTOR_H

class Functor { public:
	virtual ~Functor() {}
	virtual void Invoke(void* ctx) = 0;
};

#endif