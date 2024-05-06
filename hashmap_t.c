#include "hashmap_t.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct hashNode
{
	struct hashNode* next;
	char* data;
	unsigned dataSize;
	unsigned counter;
};

struct hashmap_t
{
	struct hashNode** hash;
	unsigned hashSize;
};

struct hashmap_t* hashmap_create(unsigned size)
{
	struct hashmap_t* hM = NULL;

	if (!size)
		return NULL;

	hM = calloc(1, sizeof(struct hashmap_t));
	if (!hM)
		abort();

	hM->hash = calloc(size, sizeof(struct hashNode*));
	if (!(hM->hash))
		abort();

	hM->hashSize = size;

	return hM;
}

unsigned key(void* data, unsigned size)
{
	unsigned h = 0, d = 0, i = 0;
	unsigned char* cData = (unsigned char*)data;

	for (i; i < size; ++i)
	{
		d = cData[i];
		d <<= i % 8;
		h ^= d;
	}

	return h;
}

struct hashNode* findDataInBucket(struct hashNode* bucket, char* data, unsigned dataSize)
{
	unsigned i = 0;

	while (bucket)
	{
		if (bucket->dataSize == dataSize)
			for (i = 0; i < dataSize; ++i)
				if (bucket->data[i] != data[i])
					break;

		if (i == dataSize)
			return bucket;

		bucket = bucket->next;
	}

	return NULL;
}

char* copyData(char* data, unsigned dataSize)
{
	char* d = NULL;
	unsigned i = 0;
	
	++dataSize;
	d = calloc(dataSize, sizeof(char));
	if (!d)
		abort();

	for (i; i < dataSize - 1; ++i)
		d[i] = data[i];

	d[i] = '\0';

	return d;
}

void pushDataInBucket(struct hashNode** bucket, void* data, unsigned dataSize)
{
	struct hashNode* b = (*bucket);

	b = calloc(1, sizeof(struct hashNode));
	if (!b)
		abort();

	b->data = copyData((char*)data, dataSize);
	b->dataSize = dataSize;
	b->counter = 1;

	(*bucket) = b;
}

void addData(struct hashmap_t* hMap, void* data, unsigned dataSize)
{
	struct hashNode* tmp = NULL;
	unsigned hK = 0;

	hK = key(data, dataSize) % hMap->hashSize;

	if (!(hMap->hash[hK]))
		pushDataInBucket(&(hMap->hash[hK]), data, dataSize);
	else
	{
		tmp = findDataInBucket(hMap->hash[hK], (char*)data, dataSize);

		if (tmp)
		{
			tmp->counter += 1;
			return;
		}

		tmp = hMap->hash[hK];

		while (tmp->next)
			tmp = tmp->next;

		pushDataInBucket(&(tmp->next), data, dataSize);
	}
}

struct hashNode* findData(struct hashmap_t* hMap, void* data, unsigned dataSize)
{
	struct hashNode* fD = NULL;
	unsigned hK = 0;

	hK = key(data, dataSize) % hMap->hashSize;
	fD = findDataInBucket(hMap->hash[hK], (char*)data, dataSize);

	return fD;
}

void printHashMap(const struct hashmap_t* hMap)
{
	unsigned i = 0;
	struct hashNode* tmp;

	for (i; i < hMap->hashSize; ++i)
	{
		tmp = hMap->hash[i];

		while (tmp)
		{
			printf("%s ", tmp->data);
			tmp = tmp->next;
		}

		printf("\n");
	}
}

void deleteHashMap(struct hashmap_t* hMap)
{
	unsigned i = 0;
	struct hashNode* tmp = NULL;

	for (i; i < hMap->hashSize; ++i)
	{
		tmp = hMap->hash[i];
		while (tmp)
		{
			free(hMap->hash[i]->data);
			hMap->hash[i]->data = NULL;
			hMap->hash[i] = hMap->hash[i]->next;
			free(tmp);
			tmp = hMap->hash[i];
		}
	}
	tmp = NULL;

	free(hMap->hash);
	hMap->hash = NULL;
	free(hMap);
}

unsigned nodeCounter(const struct hashNode* hNode)
{
	return hNode->counter;
}
