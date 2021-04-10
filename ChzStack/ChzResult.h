#ifndef CHZRESULT_H
#define CHZRESULT_H

#include <malloc.h>
#include <string.h>

enum RESULT { SUCCESS, FAIL };

typedef struct
{
	void* pData;
	int res; //RES
} ChzResult;

int ChzResult_Init(ChzResult* CR, size_t sizeData)
{
	if (sizeData == 0) { return FAIL; }

	CR->pData = malloc(sizeData);
	if (CR->pData == NULL) { return FAIL; }
	else { return SUCCESS; }
}

void ChzResult_Free(ChzResult* CR)
{
	if (CR->pData) { free(CR->pData); }
}

#endif