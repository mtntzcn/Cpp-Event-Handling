#Event handling library for pure C++

NotificationCenter developed for pure C++. That allows event handling in pure C++ like Obj-C

Objective-C:
```objectivec
[[NSNotificationCenter defaultCenter] addObserver:self
                                         selector:@selector(observeNotification1:) 
                                             name:@"notification1" 
                                           object:@"some parameter"];
    
```

In C++:
```cpp
NotificationCenter::addObserver("notification1", &obj, slot(SmpleClass, aFunction1)); // Member func
// or
NotificationCenter::addObserver("notification1", aFunction); // Non-member func
```
#####NotificationCenter allows to:

- Observe/Handle an notification/event with `NON-MEMBER FUNCTIONS` and `MEMBER-FUNCTIONS`. 
- Remove observers with notification name or with object or with member function...
- Post notification/event with notification/event name and parameter `void *`

USAGE
------------

- Copy files to your project.
- Include NofiticationCenter.hpp using #include "NotificationCenter.hpp"
- Add observer for your notification

```cpp
// For non-member functions:
NotificationCenter::addObserver("notification1", aFunction);

// For member functions:
NotificationCenter::addObserver("notification1", &obj, slot(SmpleClass, aFunction));
```
>  
> `slot/SLOT` is a Macro that creates parameter object for you. Definition:
> 
> `slot(YourClass, memberFunctionInTheClass);`
>

- Post a notification and it will be caught in your observer.

```cpp
// Without parameter:
NotificationCenter::postNotification("notification1");

// With Parameter:
NotificationCenter::postNotification("notification1", (void *)"Sample string....");
```

- Remove observers.

```cpp
// Remove all observers from object:
NotificationCenter::removeObserver(&obj);
  
// Remove all observers with notification name:
NotificationCenter::removeObservers("notification1");
  
// Remove observer with function:
NotificationCenter::removeObservers("notification1", aFunction);
  
// Remove observer with member-function:
NotificationCenter::removeObservers("notification1", slot(SmpleClass, aFunction));
```

TESTING
------------

// main.cpp

```cpp
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
```

## Output
------------
```
Hello, handleEvent1 called.
Hello, aFunction called with parameter: Some parameter
Hello, handleEvent2 called with parameter: Some parameter with counter: 2013

test2 observers has been removed.
Hello, handleEvent1 called.
Hello, World!
```




