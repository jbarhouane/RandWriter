#include <iostream>
#include <string>

#include "RandWriter.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testFreqKgram)
{
	RandWriter rWriter("abc", 4, 10);
	BOOST_REQUIRE_THROW(rWriter.freq("abcdef"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testFreqKgramChar)
{
	RandWriter rWriter("abc", 4, 10);
	BOOST_REQUIRE_THROW(rWriter.freq("abcd", ' '), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testK1gramcounter)
{
	RandWriter rWriter("abc", 4, 10);
	BOOST_REQUIRE_EQUAL(rWriter.k1gramcounter(), 4);
}

BOOST_AUTO_TEST_CASE(testGetKgram)
{
	RandWriter rWriter("abc", 3, 10);
	BOOST_REQUIRE_EQUAL(rWriter.getKgram(), "abc");
}

BOOST_AUTO_TEST_CASE(testInvalidKgramGenerate)
{
	RandWriter rWriter("abc", 3, 10);
	BOOST_REQUIRE_THROW(rWriter.generate("abcd", 10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testInvalidKValue)
{
	BOOST_REQUIRE_THROW(RandWriter rWriter("abc", 0, 10), std::invalid_argument);
}
