#ifndef HASHMAP_T
#define HASHMAP_T

struct hashNode;
struct hashmap_t;

struct hashmap_t* hashmap_create(unsigned size);

void addData(struct hashmap_t* hMap, void* data, unsigned dataSize);
struct hashNode* findData(struct hashmap_t* hMap, void* data, unsigned dataSize);

void printHashMap(const struct hashmap_t* hMap);

void deleteHashMap(struct hashmap_t* hMap);

unsigned nodeCounter(const struct hashNode* hNode);

#endif // !HASHMAP_T

