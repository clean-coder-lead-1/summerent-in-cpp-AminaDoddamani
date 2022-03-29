#include "typewise-alert.h"
#include <stdio.h>
#include<map>

std::map<coolingType,std::pair<int,int>> tempBreach{
   {PASSIVE_COOLING,{0,35}},
   {HI_ACTIVE_COOLING,{0,45}},
   {MED_ACTIVE_COOLING,{0,40}}};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  /*switch(coolingType) {
    case PASSIVE_COOLING:
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      upperLimit = 40;
      break;
  }*/
  std::map<BreachType,std::pair<int,int>>::iterator iter;
  iter = tempBreach.find(coolingType);
  lowerLimit = (iter->second).first;
  upperLimit = (iter->second).second;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is %d\n",breachType);
 /* switch(breachType) {
    case TOO_LOW:
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }*/
}
