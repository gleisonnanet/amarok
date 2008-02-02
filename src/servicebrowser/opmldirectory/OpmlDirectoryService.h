/***************************************************************************
 *   Copyright (c) 2008  Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>    *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.          *
 ***************************************************************************/

#ifndef OPMLDIRECTORYSERVICE_H
#define OPMLDIRECTORYSERVICE_H


#include "../servicebase.h"
#include "OpmlDirectoryDatabaseHandler.h"
#include "servicesqlcollection.h"

#include "amarok.h"
#include "ContextStatusBar.h"
#include <kio/job.h>
#include <kio/jobclasses.h>


class OpmlDirectoryServiceFactory: public ServiceFactory
{
    Q_OBJECT

    public:
        OpmlDirectoryServiceFactory() {}
        virtual ~OpmlDirectoryServiceFactory() {}

        virtual void init();
        virtual QString name();
        virtual KPluginInfo info();
        virtual KConfigGroup config();
};

/**
A service for displaying, previewing and downloading music from OpmlDirectory.com

	@author 
*/
class OpmlDirectoryService : public ServiceBase
{

Q_OBJECT
public:
    OpmlDirectoryService( const QString &name );

    ~OpmlDirectoryService();

    void polish();

private slots:

    void subscribeButtonClicked();
    //void download();
    void listDownloadComplete( KJob* downloadJob);
    void listDownloadCancelled();
    void doneParsing();

    /**
    * Checks if purchase button should be enabled
    * @param selection the new selection
    */
    //void itemSelected( CollectionTreeItem * selectedItem );


private:

    QPushButton *m_updateListButton;
    QPushButton *m_subscribeButton;
    KIO::FileCopyJob * m_listDownloadJob;
    KIO::FileCopyJob *m_torrentDownloadJob;
    OpmlDirectoryDatabaseHandler * m_dbHandler;
    QString m_tempFileName;
    QString m_torrentFileName;
    ServiceSqlCollection * m_collection;
    Meta::OpmlDirectoryCategory * m_currentAlbum;
};

#endif
