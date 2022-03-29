#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(20, 20, 20) == NORMAL);
}

TEST_CASE("classifyTemperaturebreach validate return value") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,0) == TOO_LOW);
}
