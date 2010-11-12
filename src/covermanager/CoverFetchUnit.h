/****************************************************************************************
 * Copyright (c) 2009 Rick W. Chen <stuffcorpse@archlinux.us>                           *
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

#ifndef AMAROK_COVERFETCHUNIT_H
#define AMAROK_COVERFETCHUNIT_H

#include "core/meta/Meta.h"

#include <KSharedPtr>

#include <QtCore/QXmlStreamReader>

class CoverFetchPayload;
class CoverFetchSearchPayload;

namespace CoverFetch
{
    enum Option
    {
        Automatic,      //!< Automtically save cover for the specified album, if one is found
        Interactive,    //!< Opens a dialog for the user to decide, and add more searches if desired
        WildInteractive //!< As @ref Interactive, but without filtering results (used for web search)
    };

    enum ImageSize
    {
        NormalSize,     //!< Normal cover size, for storage and display
        ThumbSize       //!< Thumbnail size, for icon views
    };

    enum Source
    {
        Discogs,        //!< Use Discogs as provider for cover images
        Google,         //!< Use Google image search as provider
        LastFm,         //!< Use Last.fm as provider for cover images
        Yahoo           //!< Use Yahoo! BOSS image search as provider
    };

    typedef QHash< QString, QString > Metadata;
    typedef QHash< KUrl, Metadata > Urls;
}

/**
 * A work unit for the cover fetcher queue.
 */
class CoverFetchUnit : public QSharedData
{
public:
    typedef KSharedPtr< CoverFetchUnit > Ptr;

    CoverFetchUnit( Meta::AlbumPtr album,
                    const CoverFetchPayload *payload,
                    CoverFetch::Option opt = CoverFetch::Automatic );
    CoverFetchUnit( const CoverFetchPayload *payload, CoverFetch::Option opt );
    CoverFetchUnit( const CoverFetchSearchPayload *payload );
    ~CoverFetchUnit();

    Meta::AlbumPtr album() const;
    const QStringList &errors() const;
    CoverFetch::Option options() const;
    const CoverFetchPayload *payload() const;

    bool isInteractive() const;

    template< typename T >
        void addError( const T &error );

    bool operator==( const CoverFetchUnit &other ) const;
    bool operator!=( const CoverFetchUnit &other ) const;

private:
    Meta::AlbumPtr m_album;
    QStringList m_errors;
    CoverFetch::Option m_options;
    const CoverFetchPayload *m_payload;

    Q_DISABLE_COPY( CoverFetchUnit )
};

/**
 * An abstract class for preparing URLs suitable for fetching album covers from
 * Last.fm.
 */
class CoverFetchPayload
{
public:
    enum Type { Info, Search, Art };
    CoverFetchPayload( const Meta::AlbumPtr album, enum Type type, const CoverFetch::Source src );
    virtual ~CoverFetchPayload();

    Meta::AlbumPtr album() const { return m_album; }
    CoverFetch::Source source() const;
    enum Type type() const;
    const CoverFetch::Urls &urls() const;

protected:
    const CoverFetch::Source m_src;
    CoverFetch::Urls m_urls;

    QString sanitizeQuery( const QString &query );
    const QString  sourceString() const;
    const QString &method() const { return m_method; }

    bool isPrepared() const;
    virtual void prepareUrls() = 0;

private:
    Meta::AlbumPtr m_album;
    const QString  m_method;
    enum Type      m_type;

    Q_DISABLE_COPY( CoverFetchPayload )
};

/**
 * Prepares URL suitable for getting an album's info from Last.fm.
 */
class CoverFetchInfoPayload : public CoverFetchPayload
{
public:
    explicit CoverFetchInfoPayload( const Meta::AlbumPtr album, const CoverFetch::Source src );
    explicit CoverFetchInfoPayload( const CoverFetch::Source src, const QByteArray &xml );
    ~CoverFetchInfoPayload();

protected:
    void prepareUrls();

private:
    void prepareDiscogsUrls( const QByteArray &data );
    Q_DISABLE_COPY( CoverFetchInfoPayload )
};

/**
 * Prepares URL for searching albums on Last.fm using wild mode.
 * See \ref CoverFetch::WildInteractive mode.
 */
class CoverFetchSearchPayload : public CoverFetchPayload
{
public:
    explicit CoverFetchSearchPayload( const QString &query = QString(),
                                      const CoverFetch::Source src = CoverFetch::LastFm,
                                      unsigned int page = 0,
                                      Meta::AlbumPtr album = Meta::AlbumPtr(0) );
    ~CoverFetchSearchPayload();

    QString query() const;

protected:
    void prepareUrls();

private:
    const unsigned int m_page;
    const QString m_query;

    Q_DISABLE_COPY( CoverFetchSearchPayload )
};

/**
 * Prepares URL suitable for getting an album's cover from Last.fm.
 */
class CoverFetchArtPayload : public CoverFetchPayload
{
public:
    explicit CoverFetchArtPayload( const Meta::AlbumPtr album,
                                   const CoverFetch::ImageSize size = CoverFetch::NormalSize,
                                   const CoverFetch::Source src = CoverFetch::LastFm,
                                   bool wild = false );
    explicit CoverFetchArtPayload( const CoverFetch::ImageSize size,
                                   const CoverFetch::Source src = CoverFetch::LastFm,
                                   bool wild = false );
    ~CoverFetchArtPayload();

    bool isWild() const;

    CoverFetch::ImageSize imageSize() const;

    void setXml( const QByteArray &xml );

protected:
    void prepareUrls();

private:
    CoverFetch::ImageSize m_size;
    QString m_xml;

    /// search is wild mode?
    bool m_wild;

    /// lower, remove whitespace, and do Unicode normalization on a QString
    QString normalize( const QString &raw );

    /// lower, remove whitespace, and do Unicode normalization on a QStringList
    QStringList normalize( const QStringList &rawList );

    /// prepare urls from xml provided by Discogs
    void prepareDiscogsUrls( QXmlStreamReader &xml );

    /// prepare urls from xml provided by Last.fm
    void prepareLastFmUrls( QXmlStreamReader &xml );

    /// prepare urls from xml provided by Yahoo! Image Search
    void prepareYahooUrls( QXmlStreamReader &xml );

    /// prepare urls from xml provided by Google Image Search
    void prepareGoogleUrls();

    /// gets the value of the first available key from hash
    QString firstAvailableValue( const QStringList &keys, const QHash<QString, QString> &hash );

    Q_DISABLE_COPY( CoverFetchArtPayload )
};


Q_DECLARE_METATYPE( CoverFetchUnit::Ptr );

#endif /* AMAROK_COVERFETCHUNIT_H */
