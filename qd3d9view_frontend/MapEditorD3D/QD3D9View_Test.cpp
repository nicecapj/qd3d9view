/********************************************************************
	created:	2012/02/07
	created:	2012:7:2   8:14
	filename: 	QD3D9View_Test.cpp		
	author:		DRAGONKING(gmail.com)
	
	purpose:	test routine
*********************************************************************/
#include "QD3D9View.h"
#include "define.h"
#include "defineForTest.h"

static int g_SLodLevel = 1;
const int ChunkCellNum = 4;
const int CellSize = 5;   
bool cQD3DView::InitVBIBforTLODTest()
{
	if(pVB_)
		SAFE_RELEASE(pVB_);
	if(pIB_)
		SAFE_RELEASE(pVB_);

	CUSTOMVERTEX dat[(ChunkCellNum+1) * (ChunkCellNum+1)];

	for(int z = 0; z < (ChunkCellNum + 1); ++z)
	{
		for(int x = 0 ; x < (ChunkCellNum + 1); ++x)
		{
			float depth = rand()%10;                
			DWORD color = D3DCOLOR_ARGB(255, rand()%255, rand()%255, rand()%255);
			dat[z * (ChunkCellNum + 1) + x] = CUSTOMVERTEX(x * CellSize, z * CellSize, depth, color);
		}
	}
	if( FAILED( pDevice_->CreateVertexBuffer( (ChunkCellNum + 1) * (ChunkCellNum + 1) * sizeof( CUSTOMVERTEX ),
		D3DUSAGE_WRITEONLY,
		D3DFVF_P3F_D,
		D3DPOOL_MANAGED,
		&pVB_,
		NULL ) ) )
	{
		return false;
	}

	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( pVB_->Lock( 0, 0, ( void** )&pVertices, 0 ) ) )
		return false;
	memcpy(pVertices, dat, sizeof(dat));
	pVB_->Unlock();


	WORD* pIndices;

	if( FAILED( pDevice_->CreateIndexBuffer(ChunkCellNum * ChunkCellNum * 6 * sizeof(WORD) / (g_SLodLevel * g_SLodLevel),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIB_,
		NULL) ) )
	{
		return false;
	}

	pIB_->Lock(0, 0, (void**)&pIndices, NULL);

	int index = 0;
	for(int z = 0; z < ChunkCellNum / g_SLodLevel; ++z)
	{
		for(int x = 0 ; x < ChunkCellNum / g_SLodLevel; ++x)
		{                   
			pIndices[0 + index] = (z*(ChunkCellNum + 1) + x)      * g_SLodLevel;
			pIndices[1 + index] = ((z+1)*(ChunkCellNum + 1) + x)  * g_SLodLevel;
			pIndices[2 + index] = (z*(ChunkCellNum + 1) + x+1)    * g_SLodLevel;
			pIndices[3 + index] = (z*(ChunkCellNum + 1) + x+1)    * g_SLodLevel;
			pIndices[4 + index] = ((z+1)*(ChunkCellNum + 1) + x)  * g_SLodLevel;
			pIndices[5 + index] = ((z+1)*(ChunkCellNum + 1) + x+1) * g_SLodLevel;                 
			index += 6;
		}
	}

	pIB_->Unlock();

	return S_OK;

}


void cQD3DView::RenderSLODTileForTest()
{
	pDevice_->SetStreamSource(0, pVB_, 0, sizeof(CUSTOMVERTEX));
	pDevice_->SetIndices(pIB_);
	pDevice_->SetFVF(D3DFVF_P3F_D);
	pDevice_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 25, 0,  32/g_SLodLevel);
}