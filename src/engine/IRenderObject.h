#ifndef _IRENDEROBJECT_H_
#define _IRENDEROBJECT_H_

class IRenderObject
{
public:
	virtual void Update(float dt);
	virtual void Draw();
};

#endif //_IRENDEROBJECT_H_