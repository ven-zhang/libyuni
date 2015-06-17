#include "regex.h"




namespace Yuni
{

	Regex::Regex()
		: pPCRE(nullptr)
	{}


	Regex::Regex(const Regex& rhs)
		: pPCRE(nullptr)
	{
		compile(rhs.pPattern, nullptr);
	}


	Regex::~Regex()
	{
		if (pPCRE)
			releaseContext();
	}


	Regex::Regex(const AnyString newpattern)
		: pPCRE(nullptr)
	{
		compile(newpattern, nullptr);
	}


	inline Regex::Regex(const AnyString newpattern, String& errmsg)
		: pPCRE(nullptr)
	{
		compile(newpattern, &errmsg);
	}


	void Regex::releaseContext()
	{
		assert(pPCRE and "the method releaseContext must only be called if pPCRE != null");
		pPCRE = nullptr;
	}


	bool Regex::findAll(std::vector<Occurence>& occurences, const AnyString& text) const
	{
		occurences.clear();
		if (not text.empty())
		{
			void* context = patternFindFirst(text);
			Occurence occurence;
			while (NULL != (context = patternFindNext(occurence, context)))
				occurences.push_back(occurence);
		}
		return not occurences.empty();
	}


	bool Regex::compile(const AnyString& newpattern, String* errmsg)
	{
		// keep a copy of the given pattern, which may not be zero-terminated
		pPattern = newpattern;

		// release previous PCRE data
		if (pPCRE)
			releaseContext();



		// fallback - errmsg
		if (errmsg)
			*errmsg = "not implemented";

		// do not keep the pattern
		pPattern.clear();
		pPattern.shrink();
		return false;
	}


	void* Regex::patternFindFirst(const AnyString& text) const
	{
		assert(not text.empty() and "must be checked before");

		// context for pattern matching according the input
		void* context = nullptr;
		return context;
	}


	void* Regex::patternFindNext(Occurence& occurence, void* context) const
	{
		if (context)
		{
			// reset the occurrence if a new one has been found
			occurence.offset = 0;
			occurence.capture = "";

			// if a new occurence has not been foud, releasing the context
			patternFindEnd(context);
			context = nullptr;
		}
		return context;
	}


	void Regex::patternFindEnd(void* context) const
	{
		assert(context != nullptr and "must be checked before");
	}


	bool Regex::match(const AnyString& text) const
	{
		// TODO naive implementation
		if (not text.empty() and valid())
		{
			void* context = patternFindFirst(text);
			Occurence occurence;
			while (NULL != (context = patternFindNext(occurence, context)))
			{
				patternFindEnd(context);
				return (occurence.offset == 0 and occurence.capture.size() == text.size());
			}
		}
		return false;
	}


	template<class StringT>
	inline uint64 Regex::patternReplaceAll(StringT& text, const AnyString& replacement, const Bind<bool (const Occurence&)>* callback) const
	{
		if (text.empty() or not valid())
			return 0;

		// TODO naive implementation
		AnyString stream = text;
		uint offset = 0; // TODO use uint64 as soon as possible
		Occurence occurence;
		uint64 count = 0;

		do
		{
			// try to find the next occurence starting from the current offset

			void* context = patternFindFirst(stream);
			if (NULL != (context = patternFindNext(occurence, context)))
			{
				offset += occurence.offset;

				if (nullptr == callback or (*callback)(occurence))
				{
					++count;
					// allowed to make the replacement
					text.erase(offset, occurence.capture.size());
					if (not replacement.empty())
					{
						text.insert(offset, replacement);
						offset += replacement.size();
					}
				}
				else
				{
					// not allowed to make the replacement. but incrementing by one
					// to avoid infinite loop (always matching on the same part)
					++offset;
				}

				patternFindEnd(context);

				if (offset >= text.size())
					break;

				// working on the new substring after the replacement to avoid infinite loop
				stream.adapt(text.c_str() + offset, text.size() - offset);
			}
			else
				break; // no occurence left
		}
		while (true);

		return count;
	}



	uint64 Regex::replaceAll(String& text, const AnyString& replacement) const
	{
		return patternReplaceAll(text, replacement, nullptr);
	}

	uint64 Regex::replaceAll(Clob& text, const AnyString& replacement) const
	{
		return patternReplaceAll(text, replacement, nullptr);
	}

	uint64 Regex::replaceAll(String& text, const AnyString& replacement, const Bind<bool(const Occurence&)>& callback) const
	{
		return patternReplaceAll(text, replacement, &callback);
	}

	uint64 Regex::replaceAll(Clob& text, const AnyString& replacement, const Bind<bool(const Occurence&)>& callback) const
	{
		return patternReplaceAll(text, replacement, &callback);
	}






} // namespace Yuni
