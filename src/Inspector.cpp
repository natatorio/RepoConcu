#include "Inspector.h"

int main(int argc, char *argv[]){
  Inspector* inspector = new Inspector();
  delete inspector;
  for(int i=0; argv[i]; i++){
    std::cout << argv[i];
  }
  return 0;
}

Inspector::Inspector(){

}
