#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  shared_from_this_test.cpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/*
 * � Portions copyright (c) 2006-2007 Nokia Corporation.  All rights reserved.
*/


#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/detail/lightweight_test.hpp>

#ifdef __SYMBIAN32__
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
#endif

//

class X
{
public:

    virtual void f() = 0;

protected:

    ~X() {}
};

class Y
{
public:

    virtual boost::shared_ptr<X> getX() = 0;

protected:

    ~Y() {}
};

boost::shared_ptr<Y> createY();

void test()
{
    boost::shared_ptr<Y> py = createY();
    BOOST_TEST(py.get() != 0);
    BOOST_TEST(py.use_count() == 1);

    boost::shared_ptr<X> px = py->getX();
    BOOST_TEST(px.get() != 0);
    BOOST_TEST(py.use_count() == 2);

    px->f();

    boost::shared_ptr<Y> py2 = boost::dynamic_pointer_cast<Y>(px);
    BOOST_TEST(py.get() == py2.get());
    BOOST_TEST(!(py < py2 || py2 < py));
    BOOST_TEST(py.use_count() == 3);
}

void test2();
void test3();

int main()
{
	std_log(LOG_FILENAME_LINE,"[Test Case for shared_from_this_test]");
    test();
    test2();
    test3();
#ifdef __SYMBIAN32__
	int failures = boost::report_errors();
	if(failures)
	{
		std_log(LOG_FILENAME_LINE,"Result : Failed");
		assert_failed = true;
	}
	else
	{
		std_log(LOG_FILENAME_LINE,"Result : Passed");
	}
	std_log(LOG_FILENAME_LINE,"[End Test Case ]");
#endif
	testResultXml("shared_from_this_test");
	close_log_file();
	return failures;
}

// virtual inheritance to stress the implementation
// (prevents Y* -> impl*, enable_shared_from_this<impl>* -> impl* casts)

class impl: public X, public virtual Y, public virtual boost::enable_shared_from_this<impl>
{
public:

    virtual void f()
    {
    }

    virtual boost::shared_ptr<X> getX()
    {
        boost::shared_ptr<impl> pi = shared_from_this();
        BOOST_TEST(pi.get() == this);
        return pi;
    }
};

// intermediate impl2 to stress the implementation

class impl2: public impl
{
};

boost::shared_ptr<Y> createY()
{
    boost::shared_ptr<Y> pi(new impl2);
    return pi;
}

void test2()
{
    boost::shared_ptr<Y> pi(static_cast<impl2*>(0));
}

//

struct V: public boost::enable_shared_from_this<V>
{
};

void test3()
{
    boost::shared_ptr<V> p(new V);

    boost::shared_ptr<V> q = p->shared_from_this();
    BOOST_TEST(p == q);
    BOOST_TEST(!(p < q) && !(q < p));

    V v2(*p);

    try
    {
        boost::shared_ptr<V> r = v2.shared_from_this();
        BOOST_ERROR("v2.shared_from_this() failed to throw");
    }
    catch(boost::bad_weak_ptr const &)
    {
    }

    try
    {
        *p = V();
        boost::shared_ptr<V> r = p->shared_from_this();
        BOOST_TEST(p == r);
        BOOST_TEST(!(p < r) && !(r < p));
    }
    catch(boost::bad_weak_ptr const &)
    {
        BOOST_ERROR("p->shared_from_this() threw bad_weak_ptr after *p = V()");
    }
}
