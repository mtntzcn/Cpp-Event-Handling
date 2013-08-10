//
//  NotificationCenter.hpp
//
//  Created by Recep ASLANTAS on 8/9/13.
//  Copyright (c) 2013 Recep ASLANTAS. All rights reserved.
//

#ifndef NOTIFICATIONCENTER_H
#define NOTIFICATIONCENTER_H

#include <string>

struct IObserver {  virtual void fnHandler(void *) = 0; };

typedef void (*fnHandlerPtr) (void *);
typedef void (IObserver::*fnHandlerAsMemberPtr) (void *);

#define __memFnPtr(C, F)  &C::F
#define slot(C, fn)  reinterpret_cast<fnHandlerAsMemberPtr>(__memFnPtr(C, fn))
#define SLOT(C, fn)  reinterpret_cast<fnHandlerAsMemberPtr>(__memFnPtr(C, fn))

class NotificationCenter
{
private: NotificationCenter();
public:
  static void addObserver(const std::string& name, void (*fnHandler) (void *));
  static void addObserver(const std::string& name, void * observer,  void (IObserver::*fnHandlerAsMember) (void *));

  static void removeObservers(const std::string& name);
  static void removeObserver(const std::string& name, void (*fnHandler) (void *));
  
  static void removeObserver(void *observer);
  static void removeObserver(void *observer, const std::string& name);
  static void removeObserver(void *observer, const std::string& name, void (IObserver::*fnHandlerAsMember) (void *));
 
  static void postNotification(const std::string& name, void *obj = NULL);
} ;

#endif