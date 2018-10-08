#include "Logger.h"

Logger::Logger() {
}

Logger::~Logger() {
  fclose(this->file);
}

Logger::Logger(string& filename) {
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
  //auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
  //TODO
  return NULL;
}

string Logger::format_logline(string& text) {
  time_t rawtime;
  tm* timeinfo;
  char buffer [80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
  puts(buffer);

  stringstream stringStream;
  stringStream << "[" << buffer << "][" << getpid() << "] " << text << '\n';
  string buf = stringStream.str();
  return buf;
}

void Logger::write(string& text) {
  this->set_lock();
  string ctext = format_logline(text);
  fputs(ctext.c_str(), this->file);
  this->free_lock();
}

void Logger::write(char* text) {
  this->set_lock();
  string str(text);
  string ctext = format_logline(str);
  fputs(ctext.c_str(), this->file);
  this->free_lock();
}
