#include <boost/test/unit_test.hpp>
#include "results.h"

BOOST_AUTO_TEST_CASE(ResultIsOk_WhenValue_ThenTrue)
{
    Result<int, void*> result(1);
    BOOST_TEST(result.isOk());
    BOOST_TEST(!result.isError());
}

BOOST_AUTO_TEST_CASE(ResultIsError_WhenError_ThenTrue)
{
    Result<void*, int> result(-1);
    BOOST_TEST(result.isError());
    BOOST_TEST(!result.isOk());
}

BOOST_AUTO_TEST_CASE(ResultUnwrapOr_WhenValue_ThenReturnsIt)
{
    int valueToReturn = 5;
    Result<int, void*> result(valueToReturn);
    BOOST_CHECK_EQUAL(result.unwrapOr(10), valueToReturn);
}

BOOST_AUTO_TEST_CASE(ResultUnwrapOr_WhenError_ThenReturnsReplacementValue)
{
    Result<int, std::string> result("Failed to retrieve value");
    BOOST_CHECK_EQUAL(result.unwrapOr(10), 10);
}

BOOST_AUTO_TEST_CASE(ResultUnwrapOrElse_WhenValue_ThenReturnsIt)
{
    int valueToReturn = 5;
    Result<int, void*> result(valueToReturn);
    BOOST_CHECK_EQUAL(result.unwrapOrElse([](void* _) { return 1; }), valueToReturn);
}

BOOST_AUTO_TEST_CASE(ResultUnwrapOrElse_WhenError_ThenReturnsComputedValue)
{
    Result<int, std::string> result("Failed to retrieve value");
    BOOST_CHECK_EQUAL(result.unwrapOrElse([](const std::string& _) { return 2 * 2; }), 2 * 2);
}

BOOST_AUTO_TEST_CASE(ResultMap_WhenValue_ThenMapsItAndReturnsNewResult)
{
    std::function<int(int)> fn = [](int val) { return val * val; };
    Result<int, void*> result(5);
    Result<int, void*> actual = result.map(fn);
    BOOST_ASSERT(actual.isOk());
    BOOST_CHECK_EQUAL(actual.unwrapOr(0), 25);
}

BOOST_AUTO_TEST_CASE(ResultMap_WhenError_ThenDoesNothingWithResult)
{
    std::function<int(int)> fn = [](int val) { return val * val; };
    Result<int, std::string> result("Failed to parse a number");
    Result<int, std::string> actual = result.map(fn);
    BOOST_ASSERT(actual.isError());
    BOOST_CHECK_EQUAL(actual.unwrapOr(0), 0);
}

BOOST_AUTO_TEST_CASE(ResultEqualOp_WhenEqualForValues_ThenRetursFalse)
{
    Result<int, void*> result1(5);
    Result<int, void*> result2(5);
    BOOST_CHECK(result1 == result2);
}
