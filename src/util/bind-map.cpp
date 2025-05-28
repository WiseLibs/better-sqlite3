#include "bind-map.hpp"
#include "../better_sqlite3_impl.hpp"

BindMap::Pair::Pair(v8::Isolate *isolate, char const *name, int index)
    : name(isolate, InternalizedFromUtf8(isolate, name, -1)), index(index) {}
BindMap::Pair::Pair(v8::Isolate *isolate, Pair *pair)
    : name(isolate, pair->name), index(pair->index) {}
BindMap::BindMap(char _) {
  assert(_ == 0);
  pairs = NULL;
  capacity = 0;
  length = 0;
}
BindMap::~BindMap() {
  while (length)
    pairs[--length].~Pair();
  FREE_ARRAY<Pair>(pairs);
}
void BindMap::Add(v8::Isolate *isolate, char const *name, int index) {
  assert(name != NULL);
  if (capacity == length)
    Grow(isolate);
  new (pairs + length++) Pair(isolate, name, index);
}
void BindMap::Grow(v8::Isolate *isolate) {
  assert(capacity == length);
  capacity = (capacity << 1) | 2;
  Pair *new_pairs = ALLOC_ARRAY<Pair>(capacity);
  for (int i = 0; i < length; ++i) {
    new (new_pairs + i) Pair(isolate, pairs + i);
    pairs[i].~Pair();
  }
  FREE_ARRAY<Pair>(pairs);
  pairs = new_pairs;
}
