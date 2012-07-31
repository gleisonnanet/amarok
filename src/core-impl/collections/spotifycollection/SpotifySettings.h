#ifndef SPOTIFYSETTINGS_H_
#define SPOTIFYSETTINGS_H_

#include <kcmodule.h>
#include "SpotifyConfig.h"

namespace Ui { class SpotifyConfigWidget; }

class SpotifySettings: public KCModule
{
    Q_OBJECT

public:
        explicit SpotifySettings( QWidget *parent = 0, const QVariantList &args = QVariantList() );
    virtual ~SpotifySettings();

    void cancel();
public Q_SLOTS:
    // Methods from KCModule
    virtual void save();
    virtual void load();
    virtual void defaults();

private Q_SLOTS:
    // SpotifySettings specified methods
    void login();
    void error();

private:
    void tryLogin();
    void tryDownloadResolver();
    Ui::SpotifyConfigWidget *m_configWidget;
    SpotifyConfig m_config;
};

#endif