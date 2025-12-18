//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Users
#include "Bloated.h"
#include "Node.h"
#include "JediHotCold.h"
#include "JediRedirect.h"

JediHotCold::JediHotCold(const Bloated *const pBloated)
{
	unsigned int count = 0;
	Node* use = pBloated->GetListHead();
	while (use != nullptr)
	{
		count++;
		use = use->pNext;
	}

	this->pHotHead = new JediHotNode[count/8]();
	this->pColdHead = new JediColdNode[count]();
	this->pRedirectHead = new JediRedirect[count/8]();


	Node* old = pBloated->GetListHead();
	JediHotNode* Hot = this->pHotHead;
	JediColdNode* Cold = this->pColdHead;
	JediRedirect* Direct = this->pRedirectHead;

	int Coldc = 0;
	for (unsigned int c = 0; c < count/8; c++)
	{
		Hot[c].pRedirect = &Direct[c];
		for (unsigned int keyc = 0; keyc < 8; keyc++)
		{
			Hot[c].key[keyc] = old->key;
			Direct[c].pCold[keyc] = &Cold[Coldc];

			Cold[Coldc] = *old;

			int c2 = 0;

			Cold->mArray[0].Set(Cold[Coldc].mArray, old->mArray);

			c2 = 0;
			while (c2 < sizeof(old->name))
			{
				Cold[Coldc].name[c2] = old->name[c2];
				c2++;
			}

			old = old->pNext;
			Coldc++;
		}


		Hot[c].pNext = &Hot[c + 1];
		if (c != 0) {
			Hot[c].pPrev = &Hot[c - 1];
		}
	}
	Hot[(count / 8)-1].pNext = nullptr;
}

JediHotCold::~JediHotCold()
{
	delete[] this->pHotHead;
	delete[] this->pColdHead;
	delete[] this->pRedirectHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool JediHotCold::FindKey(int key, JediColdNode *&pFoundColdNode, JediHotNode *&pFoundHotNode)
{
	JediHotNode* currentHot = this->pHotHead;

	while (currentHot != nullptr)
	{
		for (unsigned int keyc = 0; keyc < 8; keyc++)
		{
			if (currentHot->key[keyc] == key)
			{
				pFoundHotNode = currentHot;
				pFoundColdNode = currentHot->pRedirect->pCold[keyc];
				return true;
			}
			/*if (currentHot->pRedirect->pCold[keyc]->key != currentHot->key[keyc]) {
				Trace::out("ALERT");
			}*/
		}
		currentHot = currentHot->pNext;

	}

	return false;
}

JediHotNode *JediHotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---

