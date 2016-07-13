#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

template<typename T>
class CObjectManager
{
public:
	typedef std::queue<T*, std::forward_list<T*> >	ObjectQ;

public:

	CObjectManager()
	{
		m_WorkingObjects.clear();
		m_FreeObjects.clear();
	}

	~CObjectManager()
	{
		Release();
	}

	void Release()
	{
		ReleaseQ(m_WorkingTanks);
		ReleaseQ(m_FreeTanks);
	}
	
	T* GetNewObject()
	{
		T* p = NULL;
		if (m_FreeTanks.size() > 0)
		{
			p = m_FreeTanks.front();
			m_FreeTanks.pop();
		}
		else
		{
			p = new CMoveObject();
		}

		if (p)
		{
			m_WorkingObjects.push(p);
		}

		return p;
	}

	void Tick(float dt)
	{
		ObjectQ::iterator it = m_WorkingTanks.begin();
		while (it != m_WorkingTanks.end())
		{
			T* p = *it;
			++it;
			if (p->GetReleaseFlag())
			{
				p->Release();
				m_FreeTanks.push(p);
				m_WorkingTanks.remove(p);
			}
		}
	}

private:
	void ReleaseQ(ObjectQ& qu)
	{
		while (!qu.empty())
		{
			delete qu.front();
			qu.pop();
		}
	}


	CObjectManager(const CObjectManager&);
	CObjectManager* operator=(const CObjectManager&);

private:
	ObjectQ					m_WorkingObjects;
	ObjectQ					m_FreeObjects;
};


#endif //_OBJECTMANAGER_H_