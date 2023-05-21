/*
 * container.c
 *
 *  Created on: 22 janv. 2022
 *      Author: Garnier
 */


/*
 ============================================================================
 Name        : container.c
 Author      : GarnierAndrew
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "container.h"

/*----------NODE COMPONENT----------*/
typedef struct tt_node{
	struct tt_node*m_pPrev;
	struct tt_node*m_pNext;
	void		  *m_pItem;
}t_node;

t_node*NodeNew(t_node*pPrev, t_node*pNext, void*pItem){

	t_node*pNode=(t_node*)malloc(sizeof(t_node));

	*pNode=(t_node){
		.m_pPrev=pPrev,
		.m_pNext=pNext,
		.m_pItem=pItem
	};

	if(pPrev) pPrev->m_pNext=pNode;
	if(pNext) pNext->m_pPrev=pNode;

	return pNode;
}

t_node*NodeDelReturnNext(t_node*pNodeToDel, t_ptfV pDeleteFunc){

	(pDeleteFunc) ? pDeleteFunc(pNodeToDel->m_pItem) : free(pNodeToDel->m_pItem);

	t_node*pNextNode=pNodeToDel->m_pNext;

	if(pNodeToDel->m_pPrev) pNodeToDel->m_pPrev->m_pNext=pNodeToDel->m_pNext;
	if(pNodeToDel->m_pNext) pNodeToDel->m_pNext->m_pPrev=pNodeToDel->m_pPrev;

	free(pNodeToDel);
	return pNextNode;
}

/*----------CONTAINER COMPONENT----------*/

struct s_container{
	t_node *m_pHead;
	t_node *m_pTail;
	size_t  m_szCard;
	t_ptfV  m_pDeleteFunc;
};

t_container*ContainerNew(t_ptfV pDeleteFunc){
	t_container*pContainer=(t_container*)malloc(sizeof(t_container));

	*pContainer=(t_container){
		.m_pDeleteFunc=pDeleteFunc
	};

	return pContainer;
}

t_container*ContainerDel(t_container *pContainer){
	free(ContainerFlush(pContainer));
	return NULL;
}

t_container*ContainerFlush(t_container*pContainer){
	assert(pContainer);
	while(pContainer->m_pHead){
		pContainer->m_pHead=NodeDelReturnNext(pContainer->m_pHead, NULL);
		pContainer->m_szCard--;
	}
	assert(pContainer->m_szCard==0);
	pContainer->m_pTail=NULL;
	return pContainer;
}

void*ContainerPushBack(t_container*pContainer, void*pItem){
	assert(pContainer);
		pContainer->m_pTail=NodeNew(pContainer->m_pTail, NULL, pItem);
		if(pContainer->m_szCard==0){
			assert(pContainer->m_pHead==NULL);
			pContainer->m_pHead=pContainer->m_pTail;
		}
		pContainer->m_szCard++;
		assert(pContainer->m_pTail->m_pItem==pItem);
		return pContainer->m_pTail->m_pItem;
}

void*ContainerPushFront(t_container*pContainer, void*pItem){
	assert(pContainer);
	pContainer->m_pHead=NodeNew(NULL, pContainer->m_pHead, pItem);
	if(pContainer->m_szCard==0){
		assert(pContainer->m_pTail==NULL);
		pContainer->m_pTail=pContainer->m_pHead;
	}
	pContainer->m_szCard++;
	assert(pContainer->m_pHead->m_pItem==pItem);
	return pContainer->m_pHead->m_pItem;
}


void*ContainerPushAt(t_container*pContainer, void*pItem, size_t szAt){
	assert(pContainer);
	assert(szAt>=0);
	assert(szAt<=pContainer->m_szCard);

	if(szAt==0) return ContainerPushFront(pContainer, pItem);
	if(szAt==pContainer->m_szCard) return ContainerPushBack(pContainer, pItem);

	t_node*pAt;
	if(szAt<=pContainer->m_szCard/2) {
		pAt=pContainer->m_pHead;
		for(size_t i=0;i<szAt;i++) pAt=pAt->m_pNext;

	}
	else{
		pAt=pContainer->m_pTail;
		for(size_t i=pContainer->m_szCard-1;i>szAt;i--) pAt=pAt->m_pPrev;
	}

	pAt=NodeNew(pAt->m_pPrev, pAt, pItem);
	pContainer->m_szCard++;
	assert(pAt->m_pItem==pItem);
	return pAt->m_pItem;
}


void*ContainerParse(t_container*pContainer, t_ptfVV pParseFunc, void*pParam){
	assert(pContainer);
	t_node*pParse=pContainer->m_pHead;
	while(pParse){
		if(pParseFunc(pParse->m_pItem, pParam)) return pParse->m_pItem;
		pParse=pParse->m_pNext;
	}
	return NULL;
}


void*ContainerParseDelIf(t_container*pContainer, t_ptfVV pParseFunc, void*pParam){

	assert(pContainer);
	t_node*pParse=pContainer->m_pHead;

	while(pParse){
		if(pParseFunc(pParse->m_pItem, pParam)){
			if(pContainer->m_pHead==pParse) pContainer->m_pHead=pParse->m_pNext;
			if(pContainer->m_pTail==pParse) pContainer->m_pTail=pParse->m_pPrev;
			pParse=NodeDelReturnNext(pParse, pContainer->m_pDeleteFunc);			// Delete the current node and return the next
			pContainer->m_szCard--;
		}
		else{
			pParse=pParse->m_pNext;
		}
	}
	return NULL;
}


size_t ContainerCard(const t_container*pContainer){
	assert(pContainer);
	return pContainer->m_szCard;
}











