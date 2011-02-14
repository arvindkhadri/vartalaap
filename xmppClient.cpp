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

#include <iostream>
//#include<cstdio.h>
//#include<cstdlib.h>
#include <QTextStream>
#include <QtCore/QCoreApplication>
#include "QXmppMessage.h"
#include "QXmppRosterManager.h"

#include "xmppClient.h"

xmppClient::xmppClient(QObject *parent)
    : QXmppClient(parent)
{
    /*these are the constructor-inits defining which slot (the slots are protoyped in the .h file)
    will handle which signal -!! ecthiender*/
    bool check = connect(this, SIGNAL(connected()),
        SLOT(clientConnected()));
    Q_ASSERT(check);

    check = connect(&this->rosterManager(), SIGNAL(rosterReceived()),
        SLOT(rosterReceived()));
    Q_ASSERT(check);

    /// Then QXmppRoster::presenceChanged() is emitted whenever presence of someone
    /// in roster changes
    check = connect(&this->rosterManager(),
                    SIGNAL(presenceChanged(const QString&, const QString&)),
        SLOT(presenceChanged(const QString&, const QString&)));
    Q_ASSERT(check);

    check = connect(this, SIGNAL(messageReceived(const QXmppMessage&)),
            SLOT(messageReceived(const QXmppMessage&)));
        Q_ASSERT(check);
        Q_UNUSED(check);
	
       	//check = connect(this,SIGNAL(connected()), SLOT(sendMessage(const QString &,const QString &)));
	//Q_ASSERT(check);
	//Q_UNUSED(check);
    
}

xmppClient::~xmppClient()
{

}

void xmppClient::clientConnected()
{
    std::cout<<"\nexample_2_rosterHandling:: You are now CONNECTED\n"<<std::endl;
}

void xmppClient::rosterReceived()
{
    std::cout<<"\nexample_2_rosterHandling:: Roster Received\n"<<std::endl;
    QStringList list = rosterManager().getRosterBareJids();
    QString rosterEntry = "\nRoster Received:: %1 [%2]";
    for(int i = 0; i < list.size(); ++i)
    {
        QString bareJid = list.at(i);
        QString name = rosterManager().getRosterEntry(bareJid).name();
        if(name.isEmpty())
            name = "-";
        std::cout << qPrintable(rosterEntry.arg(bareJid).arg(name)) << std::endl;
    }

}

void xmppClient::presenceChanged(const QString& bareJid,
                                 const QString& resource)
{
    QString presenceStr = "Presence Changed:: %1/%2";
    std::cout<<qPrintable(presenceStr.arg(bareJid).arg(resource))<<std::endl;

}

/*implementing rcving msgs*/
void xmppClient::messageReceived(const QXmppMessage& message)
{
    const QString from = message.from();
    const QString msg = message.body();

    if(msg.isEmpty())
            return;

    //print the message
    std::cout << qPrintable( from + ":" + msg )<< std::endl;

    /* implementing replying - currently not working - btw if you comment out the
      *marked lines, it works fine,it echoes back whatever msg was sent to this client
      (like the echoclient example) but that dsnt provide the functionality*/
    //fprintf(stdout,"\nReply?[y/N]:");
    std::cout <<"Reply"<<std::endl;
    QTextStream qtin(stdin);
    char ch;
    qtin>>ch;
    if(ch=='y'||ch=='Y')
      {
    	std::cout<<"Type your reply:"<<std::endl;
        QString mssg;
        std::string reply;
        std::getline(std::cin, reply);
	mssg = QString::fromStdString(reply);
    	const QString bareJid = "rayanon004@gmail.com";
    	sendPacket(QXmppMessage("",bareJid,mssg));
      }      

}
