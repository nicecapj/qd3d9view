/********************************************************************
	created:	2012/02/13
	created:	2012:13:2   0:20
	filename: 	cTestRoutine.h		
	author:		DRAGONKING(nicecapj@gmail.com)
	
	purpose:	테스트용 기능을 모아두는 파일
*********************************************************************/
#ifndef __TEST_ROUTINE_H__
#define __TEST_ROUTINE_H__

#include <d3d9.h>
#include <d3dx9.h>

class cQD3DView;
class cTestRoutine
{
public:
	cTestRoutine(cQD3DView* pD3DView);
	~cTestRoutine();
	
protected:
	
private:
	cQD3DView* pOwnerView_;
};

#endif /*__TEST_ROUTINE_H__*/