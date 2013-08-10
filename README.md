NotificationCenter for C++
==================

NotificationCenter developed for pure C++. That allows event handling in pure C++ like Objective-C [NSNotificationCenter defaultCenter].

NotificationCenter allows to:

- Handle/Observe an notification with NON-MEMBER FUNCTIONS and MEMBER-FUNCTIONS. 
- Remove an observer objects with notification name, with object, with with object and member function
- Post notification/event with notification name and parameter (void *)

USAGE
------------

1. Copy files to your project.
2. Include NofiticationCenter.hpp using #include "NotificationCenter.hpp"
3. Add observer for your notification

For non-member functions:  

  NotificationCenter::addObserver("notification1", aFunction);

For member functions:

  NotificationCenter::addObserver("notification1", &obj, slot(SmpleClass, aFunction));


slot/SLOT is a Macro for simplify usage:

  slot(YourClass, memberFunctionInTheClass);


4. Post a notification and it will be caught in your observer.

Without parameter:

  NotificationCenter::postNotification("notification1");
  
With Parameter:

  NotificationCenter::postNotification("notification1", (void *)"Sample string....");

5. Remove observers.

Remove all observers from object:

  NotificationCenter::removeObserver(&obj);
  
Remove all observers with notification name:

  NotificationCenter::removeObservers("notification1");
  
Remove observer with function:

  NotificationCenter::removeObservers("notification1", aFunction);
  
Remove observer with member-function:

  NotificationCenter::removeObservers("notification1", slot(SmpleClass, aFunction));
  
  
TESTING
------------

// main.cpp

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
  NotificationCenter::addObserver("test1", &obj, slot(SmpleClass, handleEvent1));
  NotificationCenter::addObserver("test2", &obj, slot(SmpleClass, handleEvent2));

  NotificationCenter::postNotification("test1");
  NotificationCenter::postNotification("test2", (void *)"Some parameter");
  NotificationCenter::postNotification("test0", (void *)"Some parameter");
  
  NotificationCenter::removeObservers("notification1");
  std::cout << "\ntest2 observers has been removed." << std::endl;
  
  NotificationCenter::postNotification("notification1");
  NotificationCenter::postNotification("test2", (void *)"Some parameter");
  NotificationCenter::postNotification("test0", (void *)"Some parameter");
  
  NotificationCenter::removeObserver(&obj);

  std::cout << "Hello, World!\n";
  return 0;
}

## Output
------------

Hello, handleEvent1 called.
Hello, aFunction called with parameter: Some parameter
Hello, handleEvent2 called with parameter: Some parameter with counter: 2013

test2 observers has been removed.
Hello, handleEvent1 called.
Hello, World!







