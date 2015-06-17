#pragma once
#include "../yuni.h"
#include "../core/string.h"
#include "../core/bind.h"
#include <vector>





namespace Yuni
{


	class YUNI_DECL Regex final
	{
	public:
		struct Occurence
		{
			//! Offset in the parent text
			uint64 offset;
			//! text that matches
			AnyString capture;
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		Regex();
		/*!
		** \brief Copy constructor
		*/
		Regex(const Regex& rhs);
		#ifdef YUNI_HAS_CPP_MOVE
		//! Move constructor
		Regex(Regex&&);
		#endif

		/*!
		** \brief Constructor with a given pattern
		*/
		explicit Regex(const AnyString newpattern);
		/*!
		** \brief Constructor with a given pattern and error message
		*/
		Regex(const AnyString newpattern, String& errmsg);

		//! Destructor
		~Regex();
		//@}


		//! \name Pattern
		//@{
		//! Get the current pattern
		const String& pattern() const;

		/*!
		** \brief (re)set the current pattern
		**
		** \param newpattern A PCRE pattern
		** \return True if the pattern is valid (e.g. has been successfully compiled)
		*/
		bool pattern(const AnyString& newpattern);

		/*!
		** \brief (re)set the current pattern (with error message)
		**
		** \param newpattern A PCRE pattern
		** \param[out] errmsg A text explains why a regexp pattern is invalid (empty if no error happened)
		** \return True if the pattern is valid (e.g. has been successfully compiled)
		*/
		bool pattern(const AnyString& newpattern, String& errmsg);

		/*!
		** \brief Get if the pattern is valid
		*/
		bool valid() const;
		//@}


		//! \name Matching
		//@{
		/*!
		** \brief Get if a text strictly matches the pattern
		*/
		bool match(const AnyString& text) const;

		/*!
		** \brief Iterate through all occurences
		**
		** This example will iterate through all ASCII characters
		** \code
		** Regex regex {"[a-z]"};
		** regex.each("HelLo 42 WOrld", [](const Regex::Occurence& occurence) -> bool {
		**	std::cout << "occurence found at offset: " << occurence.offset << ": " << occurence.capture << std::endl;
		**	return true; // continue
		** });
		** \encode
		*/
		template<class C> void each(const AnyString& text, const C& callback) const;

		/*!
		** \brief Find all occurences
		** \return True if at least one occurence has been found
		*/
		bool findAll(std::vector<Occurence>& occurences, const AnyString& text) const;
		//@}


		//! \name Replacement
		//@{
		/*!
		** \brief Replace all occurences
		** \return The number of replacement
		*/
		uint64 replaceAll(String& text, const AnyString& replacement) const;
		/*!
		** \brief Replace all occurences
		** \return The number of replacement
		*/
		uint64 replaceAll(Clob& text, const AnyString& replacement) const;

		/*!
		** \brief Replace all occurences (interactive mode)
		** \return The number of replacement
		*/
		uint64 replaceAll(String& text, const AnyString& replacement, const Bind<bool(const Occurence&)>& callback) const;

		/*!
		** \brief Replace all occurences (interactive mode)
		** \return The number of replacement
		*/
		uint64 replaceAll(Clob& text, const AnyString& replacement, const Bind<bool(const Occurence&)>& callback) const;
		//@}


		//! \name Operators
		//@{
		//! Assignment
		Regex& operator = (const Regex& rhs);
		#ifdef YUNI_HAS_CPP_MOVE
		//! Move operator
		inline Regex& operator = (Regex&& rhs);
		#endif

		//! Comparison
		bool operator == (const Regex& rhs) const;
		//! Strict weak ordering
		bool operator < (const Regex& rhs) const;
		//@}


	private:
		//! Reset/compile the pattern
		bool compile(const AnyString& newpattern, String* errmsg);
		//! Release context
		void releaseContext();
		//! low level implementation for finding an occurrence
		void* patternFindFirst(const AnyString& text) const;
		//! low level implementation for finding the next occurence
		void* patternFindNext(Occurence& occurence, void* context) const;
		//! low level implementation for release a context
		void patternFindEnd(void*) const;

		template<class StringT>
		uint64 patternReplaceAll(StringT& text, const AnyString& replacement, const Bind<bool(const Occurence&)>* callback) const;

	private:
		//! PCRE opaque struct
		void* pPCRE;
		//! The user pattern
		String pPattern;

	}; // class Regex






} // namespace Yuni

#include "regex.hxx"
