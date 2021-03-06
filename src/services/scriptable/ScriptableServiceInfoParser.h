/****************************************************************************************
 * Copyright (c) 2007 Nikolaj Hald Nielsen <nhn@kde.org>                                *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 2 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#ifndef SCRIPTABLESERVICEINFOPARSER_H
#define SCRIPTABLESERVICEINFOPARSER_H

#include "../InfoParserBase.h"
#include "ScriptableServiceMeta.h"
#include <KLocalizedString>

/**
Info parser for the scriptable services

@author Nikolaj Hald Nielsen
*/
class ScriptableServiceInfoParser : public InfoParserBase
{
Q_OBJECT
public:
    explicit ScriptableServiceInfoParser( const QString &serviceName );

    ~ScriptableServiceInfoParser() override;


    virtual void getInfo( Meta::GenrePtr genre );
    void getInfo( Meta::ArtistPtr artist ) override;
    void getInfo( Meta::AlbumPtr album )  override;
    void getInfo( Meta::TrackPtr track ) override;

private:
    QString m_serviceName;

};

#endif
