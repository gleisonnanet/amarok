/****************************************************************************************
 * Copyright (c) 2009 Kevin Funk <krf@electrostorm.net>                                 *
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

#ifndef AMAROK_KNOTIFICATIONBACKEND_H
#define AMAROK_KNOTIFICATIONBACKEND_H

#include "EngineObserver.h"

#include <KNotification>

namespace Amarok {

/**
 * A class for accessing knotify in KDE
 *
 **/
class KNotificationBackend : public QObject, public EngineObserver
{
    Q_OBJECT

public:
    static KNotificationBackend* instance();
    static void destroy();

protected:
    // Reimplemented from engineobserver
    virtual void engineStateChanged( Phonon::State state, Phonon::State oldState = Phonon::StoppedState );
    virtual void engineNewTrackPlaying();

private Q_SLOTS:
    void slotShowCurrentTrack();

private:
    KNotificationBackend();
    ~KNotificationBackend();

    static KNotificationBackend* s_instance;

    KNotification* m_notify;

    QTimer *m_timer;
};

}

#endif
