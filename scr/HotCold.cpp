//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"

HotCold::HotCold(const Bloated *const pBloated)
{
	unsigned int count = 0;
	Node* use = pBloated->GetListHead();
	while (use != nullptr)
	{
		count++;
		use = use->pNext;
	}

	this->pHotHead = new HotNode[count]();
	this->pColdHead = new ColdNode[count](); 

	Node* old = pBloated->GetListHead();
	HotNode* Hot = this->pHotHead;
	ColdNode* Cold = this->pColdHead;


	for (unsigned int c = 0; c < count; c++) {
		//Hot Info
		Hot[c].key = old->key;
		Hot[c].pNext = &Hot[c + 1];
		if (c != 0)
		{
			Hot[c].pPrev = &Hot[c - 1];
		}
		Hot[c].pCold = &Cold[c];

		//Cold Info
		Cold[c] = *old;

		Cold->mArray[0].Set(Cold[c].mArray, old->mArray);

		int c2 = 0;
		while (c2 < sizeof(old->name))
		{
			Cold[c].name[c2] = old->name[c2];
			c2++;
		}

		old = old->pNext;

	}
		
	Hot[count-1].pNext = nullptr;
	Hot[count-1].pCold = nullptr;
}

HotCold::~HotCold()
{
	delete[] this->pHotHead;
	delete[] this->pColdHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool HotCold::FindKey(int key, ColdNode *&pFoundColdNode, HotNode *&pFoundHotNode)
{

	HotNode* currentHot = this->pHotHead;

	while (currentHot != nullptr)
	{
		if (currentHot->key == key)
		{
			pFoundHotNode = currentHot;
			pFoundColdNode = currentHot->pCold;
			return true;
		}
		currentHot = currentHot->pNext;
	}

	return false;
}

HotNode *HotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

