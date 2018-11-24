#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Unpacker2Test
#include <boost/test/unit_test.hpp>
#include "./Unpacker2.h"

BOOST_AUTO_TEST_SUITE(Unpacker2TestSuite)

BOOST_AUTO_TEST_CASE( my_test1 )
{
  Unpacker2 Unpacker;
  BOOST_REQUIRE(1 == 1);
}

BOOST_AUTO_TEST_SUITE_END()
