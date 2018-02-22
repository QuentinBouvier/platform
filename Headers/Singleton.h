#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
protected:
	Singleton() { };
	~Singleton() { };

public:

	static T* getInstance()
	{
		if (m_instance == NULL)
		{
			m_instance = new T;
		}

		return (static_cast<T*> (m_instance));
	}

	static void kill()
	{
		if (m_instance != NULL)
		{
			delete m_instance;
			m_instance = 0;
		}
	}

private:

	static T *m_instance;
};

template<typename T>
	T *Singleton<T>::m_instance = NULL;

#endif /* SINGLETON_H */