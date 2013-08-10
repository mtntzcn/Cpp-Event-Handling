//
//  NotificationCenter.cpp
//
//  Created by Recep ASLANTAS on 8/9/13.
//  Copyright (c) 2013 Recep ASLANTAS. All rights reserved.
//

#include "NotificationCenter.hpp"
#include <vector>

/********************************************************************************************************************************************************/

/* Forward Declerations */
class Notification;

/* NotificationCenter Container */
static std::vector<Notification* > g_notifications;

/********************************************************************************************************************************************************/

struct Notification {
  IObserver *m_observer;
  std::string m_name;
  
  void (*m_fnHandler) (void *);
  void (IObserver::*m_fnHandlerAsMember) (void *);
  
  Notification(const std::string& name, fnHandlerPtr fnHandlerAdr)
  : m_observer(NULL), m_name(name), m_fnHandler(fnHandlerAdr), m_fnHandlerAsMember(NULL) {}
  
  Notification(IObserver *observer, const std::string& name, void (IObserver::*fnHandlerAdr) (void *) )
  : m_observer(observer), m_name(name), m_fnHandler(NULL), m_fnHandlerAsMember(fnHandlerAdr) {}
};

/********************************************************************************************************************************************************/

void NotificationCenter::addObserver(const std::string& name, void (*fnHandler) (void *)) {
  Notification *notification = new Notification(name, fnHandler);
  g_notifications.push_back(notification);
}

void NotificationCenter::addObserver(const std::string& name, void * observer,  void (IObserver::*fnHandlerAsMember) (void *)) {
  IObserver *o = static_cast<IObserver *>(observer);
  Notification *notification = new Notification(o, name, fnHandlerAsMember);
  g_notifications.push_back(notification);
}

void NotificationCenter::postNotification(const std::string& name, void *obj) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  for (; it != g_notifications.end(); it++) {
    Notification *notification = *it;
    
    if (notification->m_name != name)
      continue;
    
    if (notification->m_fnHandler != NULL) {
      notification->m_fnHandler(obj);
    } else if (notification->m_fnHandlerAsMember != NULL) {
      fnHandlerAsMemberPtr fnHandlerAsMember = notification->m_fnHandlerAsMember;
      (notification->m_observer->*fnHandlerAsMember)(obj);
    }
  }
}

void NotificationCenter::removeObserver(const std::string& name, void (*fnHandler) (void *)) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  for (; it != g_notifications.end(); it++) {
    Notification* notification = *it;
    if (notification->m_name == name && notification->m_fnHandler == fnHandler) {
      g_notifications.erase(it);
    }
  }
}

void NotificationCenter::removeObservers(const std::string& name) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  
  for (; it != g_notifications.end(); it++) {
    Notification *notification = *it;
    
    if (notification->m_name == name ) {
      g_notifications.erase(it); it--;
    }
  }
}

void NotificationCenter::removeObserver(void *observer) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  
  for (; it != g_notifications.end() && g_notifications.size() > 0; it++) {
    Notification *notification = *it;
    
    if (notification->m_observer == observer) {
      g_notifications.erase(it); it--;
    }
  }
}

void NotificationCenter::removeObserver(void *observer, const std::string& name) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  
  for (; it != g_notifications.end() && g_notifications.size() > 0; it++) {
    Notification*notification = *it;
    
    if (notification->m_name == name &&
        notification->m_observer == observer) {
      g_notifications.erase(it); it--;
    }
  }
}

void NotificationCenter::removeObserver(void *observer, const std::string& name, void (IObserver::*fnHandlerAsMember) (void *)) {
  std::vector<Notification *>::iterator it = g_notifications.begin();
  
  for (; it != g_notifications.end() && g_notifications.size() > 0; it++) {
    Notification *notification = *it;
    
    if (notification->m_name == name &&
        notification->m_fnHandlerAsMember == fnHandlerAsMember &&
        notification->m_observer == observer) {
      g_notifications.erase(it); it--;
    }
  }
}

// Static members destroyed when program exited. For make sure, we erase each item and delete each item.
class ___tmpclass {
public:
  ~___tmpclass() {
    std::vector<Notification *>::iterator it = g_notifications.begin();
    
    for (; it != g_notifications.end() && g_notifications.size() > 0; it++) {
      Notification *notification = *it;
      g_notifications.erase(it);
      
      delete notification;
      it--;
    }
    
  }
};

static ___tmpclass ___tmpobj;