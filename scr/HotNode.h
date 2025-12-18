//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef HOT_NODE_H
#define HOT_NODE_H

class ColdNode;

class HotNode
{
public:
	// You CANNOT add additional data to this class
	// You cannot rearrange the data
	HotNode *pNext;
	HotNode *pPrev;
	int		key;
	ColdNode *pCold;
};

#endif

// ---  End of File ---

