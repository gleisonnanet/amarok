/****************************************************************************************
 * Copyright (c) 2013 Konrad Zemek <konrad.zemek@gmail.com>                             *
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

#ifndef STATSYNCING_ITUNES_CONFIG_WIDGET_H
#define STATSYNCING_ITUNES_CONFIG_WIDGET_H

#include "importers/SimpleImporterConfigWidget.h"

namespace StatSyncing
{

class ITunesConfigWidget : public SimpleImporterConfigWidget
{
public:
    explicit ITunesConfigWidget( const QVariantMap &config, QWidget *parent = nullptr,
                                 Qt::WindowFlags f = {} );
    ~ITunesConfigWidget();
};

} // namespace StatSyncing

#endif // STATSYNCING_ITUNES_CONFIG_WIDGET_H
