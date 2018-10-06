/*
 * LoggerTest.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: harle
 */


#include "../Logger.h"
#include <string>
#include <sys/types.h>
#include <unistd.h>

void testLogger() {
  std::string logname("testlog");
  Logger logger(logname);
  std::string s("log-de-prueba1");
  logger.write(s);
}

void testOnFork() {
  std::string logname("testlogFork");
  Logger logger(logname);
  int pid = fork();
  std::string s("");
  if (pid)
    s.assign("log-de-padre");
  else
    s.assign("log del hijo");
  logger.write(s);
}

int main() {
  testLogger();
  testOnFork();
  return 0;
}
