#ifndef _IRENDEROBJECT_H_
#define _IRENDEROBJECT_H_

class IRenderObject
{
public:
	virtual void Draw(const sRect& dest) = 0; 
	virtual void Draw(const sRect& src, const sRect& dest) = 0;
};

#endif //_IRENDEROBJECT_H_