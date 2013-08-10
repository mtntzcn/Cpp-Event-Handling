//
//  main.cpp
//  NotificationCenter-test
//
//  Created by Recep ASLANTAS on 8/9/13.
//  Copyright (c) 2013 Recep ASLANTAS. All rights reserved.
//

#include <iostream>

#include "NotificationCenter.hpp"


void aFunction(void* prm) {
  std::cout << "Hello, aFunction called with parameter: " << (const char *)prm << std::endl;
}

class SmpleClass  {
public:
  int counter  = 0;
  
  void handleEvent1(void* prm) {
    std::cout << "Hello, handleEvent1 called." << std::endl;
  }
  
  void handleEvent2(void* prm) {
    std::cout << "Hello, handleEvent2 called with parameter: " << (const char *)prm  << " with counter: "<< counter << std::endl;
  }
};

int main(int argc, const char * argv[])
{

  SmpleClass obj;
  obj.counter = 2013;
  
  NotificationCenter::addObserver("test2", aFunction);
  NotificationCenter::addObserver( "test1", &obj, slot(SmpleClass, handleEvent1));
  NotificationCenter::addObserver( "test2", &obj, slot(SmpleClass, handleEvent2));

  NotificationCenter::postNotification("test1");
  NotificationCenter::postNotification("test2", (void *)"Some parameter");
  NotificationCenter::postNotification("test0", (void *)"Some parameter");
  
  NotificationCenter::removeObservers("test2");
  std::cout << "\ntest2 observers has been removed." << std::endl;
  
  NotificationCenter::postNotification("test1");
  NotificationCenter::postNotification("test2", (void *)"Some parameter");
  NotificationCenter::postNotification("test0", (void *)"Some parameter");
  
  NotificationCenter::removeObserver(&obj);

  std::cout << "Hello, World!\n";
  return 0;
}


/*

OUTPUT:

Hello, handleEvent1 called.
Hello, aFunction called with parameter: Some parameter
Hello, handleEvent2 called with parameter: Some parameter with counter: 2013

test2 observers has been removed.
Hello, handleEvent1 called.
Hello, World!


*/


