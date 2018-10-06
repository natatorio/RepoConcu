#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

class Logger {
private:
  int fd = 0;
  FILE* file;

public:
  Logger();
  ~Logger();

  Logger(std::string& filename);
  void write(std::string& text);

private:
  void write(std::string& text, int state);
  std::string format_logline(std::string& text);
  void set_lock();
  void free_lock();

};

#endif /* LOGGER_H_ */
