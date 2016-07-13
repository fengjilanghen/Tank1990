#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_

#define ASSERT(express) if(!(express)){ __asm{int 3};}
#define SAFE_DELETE(p) if(p){ delete p; p = NULL; }
#define ASSERT_RETURN(exp) if (!(exp)) { ASSERT(false);	return;	}
#define ASSERT_RETURN_FALSE(exp) if (!(exp)) { ASSERT(false);	return false;}

#define SINGLETON_PRIVATE_FUNCTION(theClass)  \
private: \
	theClass(); \
	theClass(const theClass&) = delete; \
	theClass* operator=(const theClass&) = delete;

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

struct sRect
{
	int left;
	int top;
	int right;
	int bottom;
};



#endif //_GLOBAL_DEF_H_