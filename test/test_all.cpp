//
// Created by luojiayi on 5/18/17.
//
#include <memory>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>


int main(int argc, char* argv[]) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}