/**
 * Author: Nikolaus Mayer, 2018 (mayern@cs.uni-freiburg.de)
 */

/// System/STL
#include <cstdlib>
#include <iostream>
/// Local files
#include "TextDecorator.h"


int main() {
  TextDecorator::TextDecorator TD(true, true);
 
  std::cout << TD.red("Here's some red text, ")
            << TD.bold("this text is bold, ")
            << TD.decorate("and this is HYPER", TextDecorator::Blue|
                                                TextDecorator::Bold|
                                                TextDecorator::Inverse)
            << '\n';

  return EXIT_SUCCESS;
}

