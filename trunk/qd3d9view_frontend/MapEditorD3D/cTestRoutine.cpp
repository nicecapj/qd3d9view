/********************************************************************
created:	2012/02/07
created:	2012:7:2   8:14
filename: 	QD3D9View_Test.cpp		
author:		DRAGONKING(nicecapj@gmail.com)

purpose:	test routine
*********************************************************************/
#include "cTestRoutine.h"
#include "QD3D9View.h"
#include "defineForTest.h"

cTestRoutine::cTestRoutine(cQD3DView* pD3DView)
{
	pOwnerView_ = pD3DView;	
}

cTestRoutine::~cTestRoutine()
{

}