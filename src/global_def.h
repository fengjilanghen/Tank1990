
#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#ifndef ASSERT
#define ASSERT(express) if(!(express)){ __asm{int 3};}
#endif 

template<class Interface>
inline void
SafeRelease(
Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != 0)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = 0;
	}
}

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p){ delete p; p = NULL; }
#endif


struct sRect
{
	int left;
	int top;
	int right;
	int bottom;
};


#endif //_GLOBAL_DEF_H_