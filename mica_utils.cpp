/*
 * This file is part of MICA, a Pin tool to collect
 * microarchitecture-independent program characteristics using the Pin
 * instrumentation framework.
 *
 * Please see the README.txt file distributed with the MICA release for more
 * information.
 */

/* MICA includes */
#include "mica_utils.h"

/* lookup memNode for key in table
 * returns NULL is no such memNode is found
 */
memNode* lookup(nlist** table, ADDRINT key){

	nlist* np;

	for (np = table[key % MAX_MEM_TABLE_ENTRIES]; np != (nlist*)NULL; np = np->next){
		if(np-> id == key)
			return np->mem;
	}

	return (memNode*)NULL;
}

/* install new memNode in table */
memNode* install(nlist** table, ADDRINT key){

	nlist* np;
	ADDRINT index;

	index = key % MAX_MEM_TABLE_ENTRIES;

	np = table[index];

	if(np == (nlist*)NULL) {
		np = (nlist*)checked_malloc(sizeof(nlist));
		table[index] = np;
	}
	else{
		while(np->next != (nlist*)NULL){
			np = np->next;
		}
		np->next = (nlist*)checked_malloc(sizeof(nlist));
		np = np->next;
	}
	np->next = (nlist*)NULL;
	np->id = key;
	np->mem = (memNode*)checked_malloc(sizeof(memNode));
	for(ADDRINT i = 0; i < MAX_MEM_ENTRIES; i++){
		(np->mem)->timeAvailable[i] = 0;
	}
	for(ADDRINT i = 0; i < MAX_MEM_BLOCK; i++){
		(np->mem)->numReferenced[i] = false;
	}
	return (np->mem);
}

