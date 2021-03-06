#pragma once
#include "rwmutex.h"



namespace Yuni
{

	inline RWMutex::RWMutex(uint maxReaders)
		# ifndef YUNI_NO_THREAD_SAFE
		: pSemaphore(maxReaders), pMutex()
		# endif
	{
	}


	inline RWMutex::~RWMutex()
	{
	}


	inline RWMutex::RWMutex(const RWMutex& copy)
		# ifndef YUNI_NO_THREAD_SAFE
		: pSemaphore(copy.pSemaphore), pMutex()
		# endif
	{
	}


	inline RWMutex& RWMutex::operator = (const RWMutex&)
	{
		// Does nothing on purpose
		return *this;
	}


	inline void RWMutex::readLock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pSemaphore.acquire();
		# endif
	}


	inline void RWMutex::readUnlock()
	{
		# ifndef YUNI_NO_THREAD_SAFE
		pSemaphore.release();
		# endif
	}





	inline ReadMutexLocker::ReadMutexLocker(RWMutex& m) :
		pMutex(m)
	{
		m.readLock();
	}


	inline ReadMutexLocker::~ReadMutexLocker()
	{
		pMutex.readUnlock();
	}


	inline WriteMutexLocker::WriteMutexLocker(RWMutex& m) :
		pMutex(m)
	{
		m.writeLock();
	}


	inline WriteMutexLocker::~WriteMutexLocker()
	{
		pMutex.writeUnlock();
	}




} // namespace Yuni

