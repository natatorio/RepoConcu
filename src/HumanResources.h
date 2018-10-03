/*
 * HumanResources.h
 *
 *  Created on: Oct 3, 2018
 *      Author: harle
 */

#ifndef HUMANRESOURCES_H_
#define HUMANRESOURCES_H_

struct Passenger {
  int id;
  short int ticket;
  short int origin;
  short int destination;
  short int tourist;
};

class HumanResources {
public:
  HumanResources();
  virtual ~HumanResources();
};

#endif /* HUMANRESOURCES_H_ */
