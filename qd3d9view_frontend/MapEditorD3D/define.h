/********************************************************************
	created:	2012/02/05
	created:	2012:5:2   2:38
	filename: 	define.h		
	author:		DRAGONKING(gmail.com)
	
	purpose:	common define
*********************************************************************/
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <vector>
#include <list>
#include <map>
#include <string>
#include <d3d9types.h>

#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }

template<typename T>
void SafeDeleteMap(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; ++it)
	{
		SAFE_DELETE(it->second);
	}
	con.clear();
}

template<typename T>
void SafeDeleteVector(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; ++it)
	{
		SAFE_DELETE(*it);
	}
	con.clear();
}

template<typename T>
void SafeReleaseMap(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; ++it)
	{
		SAFE_RELEASE(it->second);
	}
	con.clear();
}

template<typename T>
void SafeReleaseVector(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; ++it)
	{
		SAFE_RELEASE(*it);
	}
	con.clear();
}
#endif /*__DEFINE_H__*/