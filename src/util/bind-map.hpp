#ifndef BETTER_SQLITE3_UTIL_BIND_MAP_HPP
#define BETTER_SQLITE3_UTIL_BIND_MAP_HPP

#include "../better_sqlite3_deps.hpp"

class BindMap {
public:
  class Pair {
    friend class BindMap;

  public:
    int GetIndex();
    v8::Local<v8::String> GetName(v8::Isolate *isolate);

  private:
    explicit Pair(v8::Isolate *isolate, char const *name, int index);
    explicit Pair(v8::Isolate *isolate, Pair *pair);
    v8::Global<v8::String> const name;
    int const index;
  };
  explicit BindMap(char _);
  ~BindMap();
  Pair *GetPairs();
  int GetSize();
  void Add(v8::Isolate *isolate, char const *name, int index);

private:
  void Grow(v8::Isolate *isolate);
  Pair *pairs;
  int capacity;
  int length;
};
LZZ_INLINE int BindMap::Pair::GetIndex() { return index; }
LZZ_INLINE v8::Local<v8::String> BindMap::Pair::GetName(v8::Isolate *isolate) {
  return name.Get(isolate);
}
LZZ_INLINE BindMap::Pair *BindMap::GetPairs() { return pairs; }
LZZ_INLINE int BindMap::GetSize() { return length; }

#endif // BETTER_SQLITE3_UTIL_BIND_MAP_HPP
