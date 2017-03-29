/* Behorende bij Programmeertechnieken huiswerk 3: unit testing.
 */

#include "mystack.h"
#define BOOST_TEST_MODULE MyStackTest
#include <boost/test/unit_test.hpp>

#include <vector>

/* Explicitly instantiate template classes for the sake of code
 * coverage generation.
 * http://stackoverflow.com/a/19792966
 */
template class MyStack<int>;
template void MyStack<int>::push_multiple<std::vector<int>::iterator>(std::vector<int>::iterator, std::vector<int>::iterator);


BOOST_AUTO_TEST_SUITE(mystack_test)

BOOST_AUTO_TEST_CASE(mystack_push)
{
  MyStack<int> stack;

  stack.push(10);
  BOOST_CHECK_EQUAL(stack.peek(), 10);
  BOOST_CHECK_EQUAL(stack.size(), 1UL);
  stack.push(20);
  BOOST_CHECK_EQUAL(stack.peek(), 20);
  BOOST_CHECK_EQUAL(stack.size(), 2UL);
  stack.push(30);
  BOOST_CHECK_EQUAL(stack.peek(), 30);
  BOOST_CHECK_EQUAL(stack.size(), 3UL);
  stack.push(40);
  BOOST_CHECK_EQUAL(stack.peek(), 40);
  BOOST_CHECK_EQUAL(stack.size(), 4UL);
}

/* TODO: more tests here ... */

BOOST_AUTO_TEST_SUITE_END()
