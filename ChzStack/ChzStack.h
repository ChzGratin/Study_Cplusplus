#ifndef CHZSTACK_H
#define CHZSTACK_H

#include <malloc.h>
#include <string.h>
#include "ChzResult.h"

typedef struct
{
	void* arrData;
	int sizeEle; //size of Element
	int sizeStack;
	int idxTop;
} ChzStack;

int ChzStack_Init(ChzStack* CS, size_t sE, size_t sS)
{
	if (sE <= 0) { return FAIL; }
	if (sS <= 1) { sS = 10; }

	CS->sizeEle = sE;
	CS->sizeStack = sS;
	CS->idxTop = -1;

	CS->arrData = malloc(sE*sS);
	if (CS->arrData == NULL) { return FAIL; }
	else { return SUCCESS; }
}

int ChzStack_isEmpty(ChzStack* CS) { return CS->idxTop < 0; }
int ChzStack_isFull(ChzStack* CS) { return CS->idxTop >= CS->sizeStack - 1; }

int ChzStack_Push(ChzStack* CS, void* pData)
{
	if (!ChzStack_isFull(CS))
	{
		memcpy((void*)((int)(CS->arrData) + CS->sizeEle * ++(CS->idxTop)), pData, CS->sizeEle);
		return SUCCESS;
	}
	else { return FAIL; }
}

void ChzStack_Pop(ChzStack* CS, ChzResult* CR)
{
	if (!ChzStack_isEmpty(CS))
	{
		memcpy(CR->pData, (void*)((int)(CS->arrData) + CS->sizeEle * (CS->idxTop)--), CS->sizeEle);
		CR->res = SUCCESS;
	}
	else { CR->res = FAIL; }
}

void ChzStack_Peek(ChzStack* CS, ChzResult* CR)
{
	if (!ChzStack_isEmpty(CS))
	{
		memcpy(CR->pData, (void*)((int)(CS->arrData) + CS->sizeEle * CS->idxTop), CS->sizeEle);
		CR->res = SUCCESS;
	}
	else { CR->res = FAIL; }
}

void ChzStack_Free(ChzStack* CS)
{
	if (CS->arrData) { free(CS->arrData); }
}

#endif