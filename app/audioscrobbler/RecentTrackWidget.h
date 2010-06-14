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

#include <QWidget>
#include <lastfm/Track>

class RecentTrackWidget : public QWidget
{
    Q_OBJECT
public:
    RecentTrackWidget( Track& track );

    Track track() const { return m_track;}

private slots:
    void onLoveToggled( bool loved );

    void onLoveClicked();
    void onTagClicked();
    void onShareClicked();

private:
    struct
    {
        class QLabel* title;
        class QLabel* albumArt;
        class QLabel* love;
        class QToolButton* cog;
    } ui;

    Track m_track;
};