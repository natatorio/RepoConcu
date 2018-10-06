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
  for(int i = 2; argv[i]; i++)  addShip(argv[i]);
  srand(time(NULL) && (int)getpid());
}

void SignalSender::addShip(char *ship){
  ships.push_back((pid_t)atoi(ship));
}

pid_t SignalSender::getRandomShip(){
  return ships[rand()%ships.size()];
}

void SignalSender::startSending(){
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    sleep(sleepTime);
    kill(getRandomShip(), signum);
  }
}

SignalSender::~SignalSender(){

}
