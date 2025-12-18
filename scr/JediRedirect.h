//-----------------------------------------------------------------------------
// Copyright 2025, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef JEDI_REDIRECT_H
#define JEDI_REDIRECT_H

#include "JediHotNode.h"
class JediColdNode;

class JediRedirect
{
public:
	// You CANNOT add additional data to this class
	// You cannot rearrange the data
	JediColdNode *pCold[ JediHotNode::KeyMax ];
};

#endif

// ---  End of File ---

