#pragma once
class Memory
{
public:
	Memory();
	~Memory();

	template<typename type>
	static type read(DWORD ptr)
	{
		type tmp;
		SIZE_T numread;
		ReadProcessMemory((HANDLE)-1, (LPVOID)ptr, &tmp, sizeof(type), &numread);
		return tmp;
	}
	static bool isReadable(DWORD ptr)
	{
		DWORD tmp;
		SIZE_T numread;
		return ReadProcessMemory((HANDLE)-1, (LPVOID)ptr, &tmp, sizeof(DWORD), &numread);
	}
};

template<typename type>
class lvar
{
public:
	lvar(type &ptr)
	{
		var = ptr;
	};
	~lvar()
	{
	};
	void set(type value) { *&var = value; }
	type get() const { return var; }
	auto operator==(type const p)
		-> bool
	{
		return var == p;
	}
	auto operator<<=(type const p) // set operatoru
		-> type
	{
		return var;
	}

	auto operator>>=(type const &p) // get operatoru
		-> type
	{
		var = p;
		return var;
	}

	//not: Delir kudur Rexy C++ get set ez s.q >> all
private:
	type var;
};

class CriticalSection
{
public:
	CriticalSection()
	{
		InitializeCriticalSection(&_native);
	}

	 ~CriticalSection()
	{
		DeleteCriticalSection(&_native);
	}

	void lock()
	{
		EnterCriticalSection(&_native);
	}

	void unlock()
	{
		LeaveCriticalSection(&_native);
	}

private:
	CRITICAL_SECTION _native;
};
class CSLock
{
public:
	CSLock(CriticalSection& cs)
		: _cs(cs)
	{
		cs.lock();
	}

	 ~CSLock()
	{
		_cs.unlock();
	}

private:
	CSLock(const CSLock&) = delete;
	CSLock& operator = (const CSLock&) = delete;

private:
	CriticalSection & _cs;
};