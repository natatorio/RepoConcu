#ifndef SIGNALSENDER_H_
#define SIGNALSENDER_H_

#include "SignalSender.h"

int main(int argc, char *argv[]){
  SignalSender* signalSender = new SignalSender(argv);
  signalSender->startSending();
  delete signalSender;
  exit(0);
}

SignalSender::SignalSender(char *argv[]){
  SignalHandler :: getInstance()->registrarHandler(SIGINT,&sigintHandler, 0);
  signum = atoi(argv[0]);
  sleepTime = atoi(argv[1]);
  for(int i = 2; argv[i]; i++)  addShip((pid_t)atoi(argv[i]));
  srand(getpid());
}

void SignalSender::addShip(pid_t shipPid){
  ships.push_back(shipPid);
}

pid_t SignalSender::getRandomShip(){
  return ships[rand() % ships.size()];
}

void SignalSender::startSending(){
  sleep(sleepTime);
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    kill(getRandomShip(), signum);
    sleep(sleepTime);
  }
}

SignalSender::~SignalSender(){

}

#endif /* SIGNALSENDER_H_ */
