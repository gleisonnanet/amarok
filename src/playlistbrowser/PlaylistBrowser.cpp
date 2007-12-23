/* This file is part of the KDE project
   Copyright (C) 2007 Bart Cerneels <bart.cerneels@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/

#include "amarok.h"
#include "PlaylistBrowser.h"
#include "Playlist.h"
#include "PodcastMeta.h"
#include "PodcastModel.h"
#include "PodcastCategory.h"

#include <kicon.h>
#include <klocale.h>

#include <QHeaderView>
#include <QToolBox>
#include <QTreeView>

namespace PlaylistBrowserNS {

PlaylistBrowser::PlaylistBrowser( const char *name )
 : KVBox()
{
    setObjectName( name );
    QToolBox *toolBox = new QToolBox( this );
    PodcastModel *podcastModel = new PodcastModel();

    m_podcastCategory = new PodcastCategory( podcastModel );

    toolBox->addItem( new QTreeView( toolBox ),
            KIcon( Amarok::icon( "playlist" ) ) , QString("Playlists") );
    toolBox->addItem( m_podcastCategory, KIcon( Amarok::icon( "playlist" ) ) , i18n("Podcasts") );
    toolBox->addItem( new QTreeView( toolBox ),
            KIcon( Amarok::icon( "playlist" ) ) , QString("Streams") );
}


PlaylistBrowser::~PlaylistBrowser()
{
}


}
