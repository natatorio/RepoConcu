#include "Logger.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

Logger::Logger() {}

Logger::~Logger() {}

Logger::Logger(std::string& filename) {
  //this->fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC);
  this->file = fopen(filename.c_str(), "w");
  this->fd = fileno(this->file);
}

Logger::Logger(std::string& filename, int state) : logfile(filename), state(state) {}

void Logger::set_lock() {
  struct flock fl;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fl.l_type = F_WRLCK;
  fcntl(this->fd, F_SETLK, fl);
}

void Logger::free_lock() {
  struct flock fl;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fl.l_type = F_UNLCK;
  fcntl(this->fd, F_SETLK, fl);
}

char* Logger::format_logline(std::string& text) {
  return text.c_str();
}

void Logger::write(std::string& text) {
  this->set_lock();
  char *ctext = format_logline(text);
  int len = strlen(ctext);
  fputs(ctext, this->file);
  this->free_lock();
}
