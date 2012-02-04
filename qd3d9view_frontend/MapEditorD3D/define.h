#ifndef __DEFINE_H__

#include <vector>
#include <list>
#include <map>
#include <d3d9types.h>

#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }

template<typename T>
void SafeDeletaMap(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; +it)
	{
		SAFE_DELETE(it->second);
	}
	con.clear();
}

template<typename T>
void SafeDeletaVector(T& con)
{
	T::iterator it = con.begin();
	T::iterator eit = con.end();
	for(it ; it != eit ; +it)
	{
		SAFE_DELETE(*it);
	}
	con.clear();
}


#endif /*__DEFINE_H__*/