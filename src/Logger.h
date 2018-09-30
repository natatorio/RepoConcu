#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

class Logger {
private:
  std::ofstream logfile;
  int state = 0;

  int fd = 0;
  FILE* file;

public:
  Logger();
  ~Logger();

  Logger(std::string& filename);
  Logger(std::string& filename, int state);

  void debug(std::string& text);
  void info(std::string& text);
  void error(std::string& text);
  void write(std::string& text);

private:
  void write(std::string& text, int state);
  char* format_logline(std::string& text);
  void set_lock();
  void free_lock();

};

#endif /* LOGGER_H_ */
