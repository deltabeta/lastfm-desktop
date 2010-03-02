/*
   Copyright 2005-2009 Last.fm Ltd. 
      - Primarily authored by Max Howell, Jono Cole and Doug Mansell

   This file is part of the Last.fm Desktop Application Suite.

   lastfm-desktop is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   lastfm-desktop is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with lastfm-desktop.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "TrackWidget.h"
#include "lib/unicorn/TrackImageFetcher.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>


TrackWidget::TrackWidget( const lastfm::Track& track )
    :m_track( track )
{    
    QHBoxLayout* h = new QHBoxLayout( this );
    h->addWidget( ui.image = new QLabel );
    ui.image->setFixedSize(50, 50);

    h->addWidget( ui.description = new QLabel );

    ui.image->setScaledContents( true );

    // start fetching the image
    m_fetcher = new TrackImageFetcher( track );
    connect( m_fetcher, SIGNAL(finished( QImage )), SLOT(onCoverDownloaded( QImage )) );
    m_fetcher->start();

    setType( Track );
}

void TrackWidget::setType( Type type )
{
    m_type = type;

    switch ( m_type )
    {
        case Artist:
            ui.description->setText( m_track.artist().name() );
            ui.image->setPixmap( ui.artistImage );
            break;
        case Album:
            ui.description->setText( m_track.album().title() + "\nby " + m_track.artist().name() );
            ui.image->setPixmap( ui.albumImage );
            break;
        case Track:
            ui.description->setText(  m_track.title() + "\nby " + m_track.artist().name() + "\nfrom " + m_track.album().title() );
            ui.image->setPixmap( ui.albumImage );
            break;
    }
}

void
TrackWidget::onCoverDownloaded( const QImage& image )
{
    ui.albumImage = QPixmap::fromImage( image );

    setType( m_type );

    sender()->deleteLater();
}
