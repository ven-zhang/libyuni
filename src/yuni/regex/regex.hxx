#pragma once
#include "regex.h"




namespace Yuni
{

	#ifdef YUNI_HAS_CPP_MOVE
	//! Move constructor
	inline Regex::Regex(Regex&& rhs)
		: pPCRE(rhs.pPCRE)
		, pPattern(std::move(rhs.pPattern))
	{
		rhs.pPCRE = nullptr;
	}
	#endif

	inline const String& Regex::pattern() const
	{
		return pPattern;
	}


	inline bool Regex::valid() const
	{
		return nullptr != pPCRE;
	}


	inline bool Regex::pattern(const AnyString& newpattern)
	{
		return compile(newpattern, nullptr);
	}


	inline bool Regex::pattern(const AnyString& newpattern, String& errmsg)
	{
		errmsg.clear();
		return compile(newpattern, &errmsg);
	}





	inline Regex& Regex::operator = (const Regex& rhs)
	{
		if (this != &rhs)
			compile(rhs.pPattern, nullptr); // naive implementation
		return *this;
	}

	#ifdef YUNI_HAS_CPP_MOVE
	//! Move constructor
	inline Regex& Regex::operator = (Regex&& rhs)
	{
		if (this != &rhs)
		{
			if (pPCRE)
				releaseContext();
			pPCRE = rhs.pPCRE;
			rhs.pPCRE = nullptr;
			pPattern = std::move(rhs.pPattern);
		}
		return *this;
	}
	#endif


	inline bool Regex::operator == (const Regex& rhs) const
	{
		return pPattern == rhs.pPattern;
	}


	inline bool Regex::operator < (const Regex& rhs) const
	{
		return pPattern < rhs.pPattern;
	}



	template<class C>
	inline void Regex::each(const AnyString& text, const C& callback) const
	{
		if (text.empty() or not valid())
			return;

		void* context = patternFindFirst(text);

		Occurence occurence;
		while (NULL != (context = patternFindNext(occurence, context)))
		{
			if (not callback(occurence))
				break;
		}

		if (context)
			patternFindEnd(context);
	}





} // namespace Yuni
