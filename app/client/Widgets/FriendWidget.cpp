
#include <QHBoxLayout>

#include <lastfm/RadioStation.h>
#include <lastfm/User.h>
#include <lastfm/Track.h>
#include <lastfm/XmlQuery.h>

#include "lib/unicorn/widgets/AvatarWidget.h"
#include "lib/unicorn/widgets/Label.h"
#include "PlayableItemWidget.h"

#include "FriendWidget.h"



FriendWidget::FriendWidget( const lastfm::XmlQuery& user, QWidget *parent)
    :StylableWidget( parent ), m_user( user )
{   
    QHBoxLayout* layout = new QHBoxLayout( this );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->setSpacing( 0 );

    layout->addWidget( ui.avatar = new AvatarWidget( this ) );
    ui.avatar->setObjectName( "avatar" );

    QRegExp re( "/serve/(\\d*)s?/" );

    ui.avatar->loadUrl( user["image size=medium"].text().replace( re, "/serve/\\1s/" ), false );
    ui.avatar->setHref( user["url"].text() );

    QVBoxLayout* vl = new QVBoxLayout();
    vl->setContentsMargins( 0, 0, 0, 0 );
    vl->setSpacing( 0 );
    layout->addLayout( vl, 1 );

    vl->addWidget( ui.name = new Label( user["name"].text(), this) );
    ui.name->setObjectName( "name" );

    vl->addWidget( ui.details = new Label( "", this) );
    ui.details->setObjectName( "details" );

    lastfm::MutableTrack recentTrack;
    recentTrack.setTitle( user["recenttrack"]["name"].text() );
    recentTrack.setAlbum( user["recenttrack"]["album"]["name"].text() );
    recentTrack.setArtist( user["recenttrack"]["artist"]["name"].text() );

    vl->addWidget( ui.lastTrack = new Label( tr( "Last track: %1" ).arg( recentTrack.toString() ), this) );
    ui.lastTrack->setObjectName( "lastTrack" );

    QHBoxLayout* radios = new QHBoxLayout;
    radios->setContentsMargins( 0, 0, 0, 0 );
    radios->setSpacing( 0 );

    vl->addLayout( radios );

    radios->addWidget( ui.radio = new PlayableItemWidget( RadioStation::library( User( user["name"].text() ) ), tr( "Play Library Radio" ) ) );
    ui.lastTrack->setObjectName( "radio" );

//    QList<User> users;
//    users << User() << User( user["name"].text() );

//    radios->addWidget( ui.multiRadio = new PlayableItemWidget( RadioStation::library( users ), tr( "Play Combo Radio" ) ) );
//    ui.lastTrack->setObjectName( "multiRadio" );

    connect( lastfm::UserDetails::getInfo( user["name"].text() ), SIGNAL(finished()), SLOT(onGotInfo()));
}


void
FriendWidget::onGotInfo()
{
    lastfm::UserDetails user( qobject_cast<QNetworkReply*>(sender()) );

    ui.avatar->setUserDetails( user );
    ui.details->setText( user.getInfoString() );
}

QString
FriendWidget::name() const
{
    return m_user["name"].text();
}

QString
FriendWidget::realname() const
{
    return m_user["realname"].text();
}