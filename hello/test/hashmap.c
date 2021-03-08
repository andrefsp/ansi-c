#include <assert.h>
#include <string.h>

#include "../src/hello.c"

void test_hashmap_construct() {
    Hashmap *map = NewHashmap();
    assert(("size", map->Size == 0));
}

void test_hashmap_get_and_set() {
    Hashmap *map = NewHashmap();

    map->Set(map, "key1", "value1");
    char *value1 = map->Get(map, "key1"); 
    assert(("get and set", strcmp(value1, "value1") == 0));

    map->Set(map, "key2", "value2");
    char *value2 = map->Get(map, "key2"); 
    assert(("get and set", strcmp(value2, "value2") == 0));

    char *value3 = map->Get(map, "doesnotexist"); 
    assert(("null value", !value3));
}

void test_hashmap_multiple_set_same_key() {
    Hashmap *map = NewHashmap();

    map->Set(map, "key", "value1");
    char *value = map->Get(map, "key"); 
    assert(("get and set", strcmp(value, "value1") == 0));
    assert(("size", map->Size == 1));

    map->Set(map, "key", "new_value");
    value = map->Get(map, "key"); 
    assert(("get and set", strcmp(value, "new_value") == 0));
    assert(("size after", map->Size == 1));
}


void test_hashmap_get_and_set_delete() {
    Hashmap *map = NewHashmap();

    map->Set(map, "key1", "value1");
    map->Set(map, "key2", "value2");

    map->Delete(map, "key1");
    char *value1 = map->Get(map, "key1");
    assert(("null value", !value1));

    char *value2 = map->Get(map, "key2"); 
    assert(("get and set", strcmp(value2, "value2") == 0));
}

void test_hashmap_get_and_set_ints() {
    Hashmap *map = NewHashmap();
    
    int x = 10;
    int y = 20;

    map->Set(map, "key1", &x);
    map->Set(map, "key2", &y);

    int *value1 = map->Get(map, "key1");
    assert(("key 1 equal", *value1 == 10));

    int *value2 = map->Get(map, "key2"); 
    assert(("key 2 equal", *value1 == 20));
}


void test_hashmap(void) {
    test_hashmap_construct();
    test_hashmap_get_and_set(); 
    test_hashmap_get_and_set_delete();
    test_hashmap_multiple_set_same_key(); 
}
