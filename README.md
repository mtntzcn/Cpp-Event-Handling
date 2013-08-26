#Event handling library for pure C++

NotificationCenter developed for pure C++. That allows event handling in pure C++ like Objective-C 
```objectivec
[[NSNotificationCenter defaultCenter] addObserver:self
                                         selector:@selector(observeNotification1:) 
                                             name:@"notification1" 
                                           object:@"some parameter"];
    
```
#####NotificationCenter allows to:

- Handle/Observe an notification with NON-MEMBER FUNCTIONS and MEMBER-FUNCTIONS. 
- Remove an observer objects with notification name, with object, with with object and member function
- Post notification/event with notification name and parameter (void *)

USAGE
------------

- Copy files to your project.
- Include NofiticationCenter.hpp using #include "NotificationCenter.hpp"
- Add observer for your notification

For non-member functions:  

  NotificationCenter::addObserver("notification1", aFunction);

For member functions:

  NotificationCenter::addObserver("notification1", &obj, slot(SmpleClass, aFunction));


slot/SLOT is a Macro for simplify usage:

  slot(YourClass, memberFunctionInTheClass);


- Post a notification and it will be caught in your observer.

Without parameter:

  NotificationCenter::postNotification("notification1");
  
With Parameter:

  NotificationCenter::postNotification("notification1", (void *)"Sample string....");

- Remove observers.

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


## Output
------------

Hello, handleEvent1 called.
Hello, aFunction called with parameter: Some parameter
Hello, handleEvent2 called with parameter: Some parameter with counter: 2013

test2 observers has been removed.
Hello, handleEvent1 called.
Hello, World!







