#ifndef _IGAMELEVEL_H_
#define _IGAMELEVEL_H_

class IGameLevel
{
public:
	virtual bool Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0; 
	virtual void KeyEvent(int key, bool pressed) = 0;
};

#endif //_IGAMELEVEL_H_