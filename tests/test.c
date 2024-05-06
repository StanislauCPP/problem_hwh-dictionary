#define _CRT_SECURE_NO_WARNINGS

#include "Timer.h"
#include "../hashmap_t.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void (*hMapFunction)(struct hashmap_t*, void*, unsigned);

void scanfUn(unsigned* data)
{
	int parScanf = 0;
	parScanf = scanf("%u", data);
	if (parScanf != 1)
		abort();
}

void scanfStr(char* data)
{
	int parScanf = 0;
	parScanf = scanf("%s", data);
	if (parScanf != 1)
		abort();
}

void printAmountFoundData(struct hashmap_t* hMap, void* data, unsigned dataSize)
{
	struct hashNode* hN = NULL;
	unsigned tVal = 0, resVal = 0;

	hN = findData(hMap, data, dataSize);

	if (!hN)
		printf("0 ");
	else
	{
		resVal = nodeCounter(hN);
		printf("%u ", resVal);
	}
	
	scanf("%u", &tVal);
	
	if(tVal != resVal)
	{
		deleteHashMap(hMap);
		abort();
	}
}

void strStreamHandler(struct hashmap_t* hMap, unsigned strStreamSize, hMapFunction hMF)
{
	unsigned i = 0, j = 0, rBsize = 0;
	int parScanf = 0;
	unsigned bufSize = 128;
	char* buf = NULL;
	buf = calloc(bufSize, sizeof(char));
	if (!buf)
		abort();

	for (i; i < strStreamSize; i += rBsize + 1)
	{
		scanfStr(buf);
		rBsize = strlen(buf);
		hMF(hMap, (void*)buf, rBsize);
	}

	free(buf);
	buf = NULL;
}

int main()
{
	struct hashmap_t* hashMap = NULL;
	unsigned strSize = 0;
	struct timespec t1, t2;
	
	scanfUn(&strSize);

	timespec_get(&t1, TIME_UTC);
	hashMap = hashmap_create(strSize/10);

	strStreamHandler(hashMap, strSize, &addData);

	scanfUn(&strSize);
	strStreamHandler(hashMap, strSize, &printAmountFoundData);

	deleteHashMap(hashMap);
	timespec_get(&t2, TIME_UTC);
	
	printf("\n");
	
	printf("%lf\nTest passed\n\n", diff(t1, t2));
	return 0;
}
