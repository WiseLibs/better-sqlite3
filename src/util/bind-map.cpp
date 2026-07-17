class BindMap {
public:

	// This nested class represents a single mapping between a parameter name
	// and its associated parameter index in a prepared statement.
	class Pair { friend class BindMap;
		public:

			inline int GetIndex() {
				return index;
			}

			inline Napi::String GetName(Napi::Env env) {
				return name.Value();
			}

		private:

			explicit Pair(Napi::Env env, const char* name, int index)
				: name(Napi::Persistent(InternalizedFromUtf8(env, name, -1))), index(index) {}

			explicit Pair(Napi::Env env, Pair* pair)
				: name(Napi::Persistent(pair->name.Value())), index(pair->index) {}

			const Napi::Reference<Napi::String> name;
			const int index;
	};

	explicit BindMap(char _) {
		assert(_ == 0);
		pairs = NULL;
		capacity = 0;
		length = 0;
	}

	~BindMap() {
		while (length) pairs[--length].~Pair();
		FREE_ARRAY<Pair>(pairs);
	}

	inline Pair* GetPairs() {
		return pairs;
	}

	inline int GetSize() {
		return length;
	}

	// Adds a pair to the bind map, expanding the capacity if necessary.
	void Add(Napi::Env env, const char* name, int index) {
		assert(name != NULL);
		if (capacity == length) Grow(env);
		new (pairs + length++) Pair(env, name, index);
	}

private:

	void Grow(Napi::Env env) {
		assert(capacity == length);
		capacity = (capacity << 1) | 2;
		Pair* new_pairs = ALLOC_ARRAY<Pair>(capacity);
		for (int i = 0; i < length; ++i) {
			new (new_pairs + i) Pair(env, pairs + i);
			pairs[i].~Pair();
		}
		FREE_ARRAY<Pair>(pairs);
		pairs = new_pairs;
	}

	Pair* pairs;
	int capacity;
	int length;
};
