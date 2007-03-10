 /*
  Copyright (c) 2007  Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#include "amarok.h"
#include "debug.h"
#include "magnatunecontentmodel.h"
#include "magnatunedatabasehandler.h"


MagnatuneContentModel::MagnatuneContentModel(QObject *parent, QString genre )
     : ServiceModelBase(parent)
{
     m_genre = genre;
     m_rootContentItem = new MagnatuneContentItem( m_genre );
     m_infoParser = new MagnatuneInfoParser();
     connect( m_infoParser, SIGNAL (info ( QString ) ), this, SLOT( infoParsed( QString ) ) );


    m_artistIcon = KIcon( Amarok::icon( "artist" ) );
    m_albumIcon = KIcon( Amarok::icon( "album" ) );
    m_trackIcon = KIcon( Amarok::icon( "track" ) );

     
}

MagnatuneContentModel::~MagnatuneContentModel()
{
      delete m_rootContentItem;
}

int MagnatuneContentModel::columnCount(const QModelIndex &parent) const
{

   //debug() << "MagnatuneContentModel::columnCount" << endl;


        if (parent.isValid())
         return static_cast<MagnatuneContentItem*>(parent.internalPointer())->columnCount();
     else
         return m_rootContentItem->columnCount();

}

QVariant MagnatuneContentModel::data(const QModelIndex &index, int role) const
{
    //debug() << "MagnatuneContentModel::data" << endl;
    

    if (!index.isValid())
        return QVariant();



    if (role == Qt::DisplayRole) {
        MagnatuneContentItem *item = static_cast<MagnatuneContentItem*>(index.internalPointer());
        return item->data(index.column());
    } else if ( role == Qt::DecorationRole ) {
        MagnatuneContentItem *item = static_cast<MagnatuneContentItem*>(index.internalPointer());

        if ( item->getType() == MAGNATUNE_ARTIST )
            return m_artistIcon;
        else if ( item->getType() == MAGNATUNE_ALBUM )
            return m_albumIcon;
        else if ( item->getType() == MAGNATUNE_TRACK )
            return m_trackIcon;
        else 
            return QVariant();

    } else {
        return QVariant();
    }
}

Qt::ItemFlags MagnatuneContentModel::flags(const QModelIndex &index) const
{

    //debug() << "MagnatuneContentModel::flags" << endl;
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant MagnatuneContentModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    //debug() << "MagnatuneContentModel::headerData" << endl;

         if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return "Artist / Album / Track";

     return QVariant();

}

QModelIndex MagnatuneContentModel::index(int row, int column, const QModelIndex &parent) const
{

     //debug() << "MagnatuneContentModel::index, row: " << row << ", column: " << column << endl;

     MagnatuneContentItem *parentItem;

     if (!parent.isValid())
         parentItem = m_rootContentItem;
     else
         parentItem = static_cast<MagnatuneContentItem*>(parent.internalPointer());

     MagnatuneContentItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();


}

QModelIndex MagnatuneContentModel::parent(const QModelIndex &index) const
{


      //debug() << "MagnatuneContentModel::parent" << endl; 
      if (!index.isValid()) {
         //debug() << "MagnatuneContentModel::parent, index invalid... " << endl; 
         return QModelIndex();
     }

     MagnatuneContentItem *childItem = static_cast<MagnatuneContentItem*>(index.internalPointer());
     MagnatuneContentItem *parentItem = static_cast<MagnatuneContentItem*>(childItem->parent() );

     if (parentItem == m_rootContentItem)
         //debug() << "MagnatuneContentModel::parent, root item... " << endl; 
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);


}

int MagnatuneContentModel::rowCount(const QModelIndex &parent) const
{
      // debug() << "MagnatuneContentModel::rowCount"  << endl;

      MagnatuneContentItem *parentItem;

     if (!parent.isValid())
         parentItem = m_rootContentItem;
     else
         parentItem = static_cast<MagnatuneContentItem*>(parent.internalPointer());

     return parentItem->childCount();


} 

bool MagnatuneContentModel::hasChildren ( const QModelIndex & parent ) const {

    MagnatuneContentItem* item;

     if (!parent.isValid())
         item = m_rootContentItem;
     else
         item = static_cast<MagnatuneContentItem*>(parent.internalPointer());

    return item->hasChildren();
}

void MagnatuneContentModel::setGenre( QString genre ) {

    m_genre = genre;
    delete m_rootContentItem;
    m_rootContentItem = new MagnatuneContentItem( m_genre );
    reset();

}


void MagnatuneContentModel::requestHtmlInfo ( const QModelIndex & index ) const {

    debug() << "MagnatuneContentModel::requestHtmlInfo"  << endl;
    MagnatuneContentItem* item;

    if (!index.isValid())
        item = m_rootContentItem;
    else
        item = static_cast<MagnatuneContentItem*>(index.internalPointer());


   switch ( item->getType() ) {
       case MAGNATUNE_ARTIST:
           m_infoParser->getInfo( item->getContentUnion().artistValue );
           break;
       case MAGNATUNE_ALBUM:
           m_infoParser->getInfo( item->getContentUnion().albumValue );
           break;
     }

}

void MagnatuneContentModel::infoParsed( QString infoHtml ) {
    debug() << "MagnatuneContentModel::infoParsed"  << endl;
    emit( infoChanged ( infoHtml ) );
}



#include "magnatunecontentmodel.moc"
