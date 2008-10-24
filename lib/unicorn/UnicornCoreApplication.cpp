/***************************************************************************
 *   Copyright 2005-2008 Last.fm Ltd.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#include "UnicornCoreApplication.h"
#include "lib/lastfm/ws/WsKeys.h"
#include "lib/lastfm/core/CoreDir.h"
#include "lib/lastfm/core/CoreSettings.h"
#include "lib/lastfm/core/CoreSysInfo.h"
#include "common/c++/Logger.h"
#include <QDebug>

#ifdef WIN32
extern void qWinMsgHandler( QtMsgType t, const char* msg );
#endif


UnicornCoreApplication::UnicornCoreApplication( int& argc, char** argv )
                      : QCoreApplication( argc, argv )
{
	init();
	
	CoreSettings s;
	Ws::Username = qstrdup( s.value( "Username" ).toString().toUtf8().data() );
    Ws::SessionKey = qstrdup( s.value( "SessionKey" ).toString().toUtf8().data() );
}


void //static
UnicornCoreApplication::init()
{
	QCoreApplication::setOrganizationName( CoreSettings::organizationName() );
    QCoreApplication::setOrganizationDomain( CoreSettings::organizationDomain() );

    // HI! DON'T USE OURS! GET YOUR OWN! http://www.last.fm/api
    Ws::SharedSecret = "73582dfc9e556d307aead069af110ab8";
    Ws::ApiKey = "c8c7b163b11f92ef2d33ba6cd3c2c3c3";

    CoreDir::mkpaths();

#ifdef WIN32
    QString bytes = log( applicationName() ).absoluteFilePath();
    const wchar_t* path = bytes.utf16();
#else
    QByteArray bytes = log( applicationName() ).absoluteFilePath().toLocal8Bit();
    const char* path = bytes.data();
#endif
    new Logger( path );

    qInstallMsgHandler( qMsgHandler );
    qDebug() << "Introducing" << applicationName()+'-'+applicationVersion();
    qDebug() << "Directed by" << CoreSysInfo::platform();
}


void
UnicornCoreApplication::qMsgHandler( QtMsgType type, const char* msg )
{
    Logger::the().log( msg );

#ifndef NDEBUG
#ifdef WIN32
    qWinMsgHandler( type, msg );
#else
	Q_UNUSED( type );
    fprintf( stderr, "%s\n", msg );
    fflush( stderr );
#endif
#endif
}


QFileInfo
UnicornCoreApplication::log( const QString& productName )
{
#ifdef NDEBUG
    return CoreDir::logs().filePath( productName + ".log" );
#else
    return CoreDir::logs().filePath( productName + ".debug.log" );
#endif
}