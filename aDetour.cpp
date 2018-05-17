#include <process.h>
#include <thread>
#include "adDetour.hpp"

namespace pPlat
{
	namespace Native
	{
		void* Detour::Install(void* target, void* detour, char* fncName)
		{
			auto origFunc = DetourFunction((PBYTE)target, (PBYTE)detour);
			m_detourList.push_back(DetourEntry(origFunc, target, detour, fncName));
			return origFunc;
		}

		bool Detour::RemoveHooks() const
		{
	
			for (auto hookEntry : m_detourList)
			{
				if (!DetourRemove((PBYTE)hookEntry.orig, (PBYTE)hookEntry.detour))
				{
					//Console::PrintLn("Failed to remove Hook: %p -> %p (%s) - %08x", hookEntry.detour, hookEntry.target, hookEntry.fncName, GetLastError());
				}
			}

			
			return true;
		}
	}
}