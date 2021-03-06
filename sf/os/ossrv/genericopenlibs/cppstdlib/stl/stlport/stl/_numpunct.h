/*
 * Portions Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef _STLP_INTERNAL_NUMPUNCT_H
#define _STLP_INTERNAL_NUMPUNCT_H

#ifndef _STLP_IOS_BASE_H
# include <stl/_ios_base.h>
#endif

# ifndef _STLP_C_LOCALE_H
#  include <stl/c_locale.h>
# endif

#ifndef _STLP_INTERNAL_STRING_H
# include <stl/_string.h>
#endif

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// numpunct facets

template <class _CharT> class numpunct {};
template <class _CharT> class numpunct_byname {};
template <class _Ch, class _InIt> class num_get;

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC numpunct<char> : public locale::facet
{
  friend class _Locale_impl;

#ifndef _STLP_NO_FRIEND_TEMPLATES
  template <class _Ch, class _InIt> friend class num_get;
#endif
public:
  typedef char               char_type;
  typedef string             string_type;

  explicit numpunct(size_t __refs = 0)
    : locale::facet(__refs), _M_truename("true"), _M_falsename("false") {}

  char decimal_point() const { return do_decimal_point(); }
  char thousands_sep() const { return do_thousands_sep(); }
  string grouping() const { return do_grouping(); }
  string truename() const { return do_truename(); }
  string falsename() const { return do_falsename(); }

#if defined(__SYMBIAN32__WSD__) 
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id& GetFacetLocaleId();
#elif defined (__SYMBIAN32__NO_STATIC_IMPORTS__)    
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id& GetFacetLocaleId();
  static locale::id id;        
#else
  // NOTE: Symbian doesn't support exporting static data.  
  // Users of this class should use GetFacetLocaleId() to access the data member id  
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id id;
#endif

#ifndef _STLP_NO_FRIEND_TEMPLATES
protected:
#endif

  _STLP_DECLSPEC ~numpunct();

  string  _M_truename;
  string  _M_falsename;
  string  _M_grouping;

  _STLP_DECLSPEC virtual char do_decimal_point() const;
  _STLP_DECLSPEC virtual char do_thousands_sep() const;
  _STLP_DECLSPEC virtual string do_grouping() const;
  _STLP_DECLSPEC virtual string do_truename() const;
  _STLP_DECLSPEC virtual string do_falsename()  const;
};

# if ! defined (_STLP_NO_WCHAR_T)

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC numpunct<wchar_t> : public locale::facet
{
  friend class _Locale_impl;
public:
  typedef wchar_t               char_type;
  typedef wstring               string_type;

  explicit numpunct(size_t __refs = 0)
    : locale::facet(__refs), _M_truename(L"true"), _M_falsename(L"false") {}

  wchar_t decimal_point() const { return do_decimal_point(); }
  wchar_t thousands_sep() const { return do_thousands_sep(); }
  string grouping() const { return do_grouping(); }
  wstring truename() const { return do_truename(); }
  wstring falsename() const { return do_falsename(); }

#if defined(__SYMBIAN32__WSD__) 
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id& GetFacetLocaleId();
#elif defined (__SYMBIAN32__NO_STATIC_IMPORTS__)    
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id& GetFacetLocaleId();
  static locale::id id;         
#else
  // NOTE: Symbian doesn't support exporting static data.  
  // Users of this class should use GetFacetLocaleId() to access the data member id  
  _STLP_STATIC_MEMBER_DECLSPEC static locale::id id;
#endif
  
protected:
  wstring _M_truename;
  wstring _M_falsename;
  string _M_grouping;

  _STLP_DECLSPEC ~numpunct();

  _STLP_DECLSPEC virtual wchar_t do_decimal_point() const;
  _STLP_DECLSPEC virtual wchar_t do_thousands_sep() const;
  _STLP_DECLSPEC virtual string  do_grouping() const;
  _STLP_DECLSPEC virtual wstring do_truename() const;
  _STLP_DECLSPEC virtual wstring do_falsename()  const;
};

# endif /* WCHAR_T */

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC numpunct_byname<char> : public numpunct<char> {
public:
  typedef char                char_type;
  typedef string              string_type;

  _STLP_DECLSPEC explicit numpunct_byname(const char* __name, size_t __refs = 0, _Locale_name_hint* __hint = 0);

protected:
	
  _STLP_DECLSPEC ~numpunct_byname();

  _STLP_DECLSPEC virtual char   do_decimal_point() const;
  _STLP_DECLSPEC virtual char   do_thousands_sep() const;
  _STLP_DECLSPEC virtual string do_grouping()      const;

private:
  _Locale_numeric* _M_numeric;

  //explicitely defined as private to avoid warnings:
  typedef numpunct_byname<char> _Self;
  numpunct_byname(_Self const&);
  _Self& operator = (_Self const&);
  friend _Locale_name_hint* _Locale_extract_hint(numpunct_byname<char>*);
};

# ifndef _STLP_NO_WCHAR_T
_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC numpunct_byname<wchar_t>: public numpunct<wchar_t> {
public:
  typedef wchar_t               char_type;
  typedef wstring               string_type;

  _STLP_DECLSPEC explicit numpunct_byname(const char* __name, size_t __refs = 0, _Locale_name_hint* __hint = 0);

protected:

  _STLP_DECLSPEC ~numpunct_byname();

  _STLP_DECLSPEC virtual wchar_t   do_decimal_point() const;
  _STLP_DECLSPEC virtual wchar_t   do_thousands_sep() const;
  _STLP_DECLSPEC virtual string    do_grouping() const;

private:
  _Locale_numeric* _M_numeric;

  //explicitely defined as private to avoid warnings:
  typedef numpunct_byname<wchar_t> _Self;
  numpunct_byname(_Self const&);
  _Self& operator = (_Self const&);
};

# endif /* WCHAR_T */

_STLP_END_NAMESPACE

#endif /* _STLP_NUMPUNCT_H */

// Local Variables:
// mode:C++
// End:

