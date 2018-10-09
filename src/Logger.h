#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <chrono>
#include <sstream>
#include <iostream>

using namespace std;

class Logger {
private:
  int fd = 0;
  FILE* file;

public:
  Logger();
  ~Logger();

  Logger(string& filename);
  Logger(const char* filename);
  void write(string& text);
  void write(char* text);
  void write(ostringstream& text);

private:
  void write(string& text, int state);
  string format_logline(string& text);
  void set_lock();
  void free_lock();

};

#endif /* LOGGER_H_ */
