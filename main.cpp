/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
 *	Manjeet Dahiya
 *
 * Source:
 *	http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#include<cstdio>
#include<iostream>
#include<cstdlib>
#include <QtCore/QCoreApplication>
#include "xmppClient.h"
#include "QXmppLogger.h"
//#include <QString.h>
#include<termios.h>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QXmppLogger::getLogger()->setLoggingType(QXmppLogger::FileLogging);

   xmppClient client;
   QString username, password;
   std::string uid,pwd;
   /*getting uid and pwd*/
   cout<<"\nEnter your gmail username:";
   std::getline(cin,uid);
   uid.append("@gmail.com");
   username = QString::fromStdString(uid);
   cout<<qPrintable(username);
   cout<<endl<<"\nEnter your password:";
   termios oldt;                                          //This has been added so that password does not echo, when typed.
   tcgetattr(STDIN_FILENO, &oldt);
   termios newt = oldt;
   newt.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   std::getline(cin,pwd);
   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);              //Returns back the old settings of the terminal/stdout
    /*connecting to server*/
   
   password = QString::fromStdString(pwd);
   client.connectToServer(username,password);


    return a.exec();
}
