#include "Logger.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <chrono>
#include <sstream>

Logger::Logger() {
}

Logger::~Logger() {
  fclose(this->file);
}

Logger::Logger(std::string& filename) {
  //this->fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC);
  this->file = fopen(filename.c_str(), "w");
  this->fd = fileno(this->file);
}

Logger::Logger(const char *filename) {
  this->file = fopen(filename, "w");
  this->fd = fileno(this->file);
}

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

char* getLocalTime() {
  //auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

}

std::string Logger::format_logline(std::string& text) {
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer [80];

  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);

  std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
  std::puts(buffer);

  std::stringstream stringStream;
  stringStream << "[" << buffer << "][" << getpid() << "] " << text << '\n';
  std::string buf = stringStream.str();
  return buf;
}

void Logger::write(std::string& text) {
  this->set_lock();
  std::string ctext = format_logline(text);
  fputs(ctext.c_str(), this->file);
  this->free_lock();
}
