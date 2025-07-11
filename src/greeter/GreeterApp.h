/***************************************************************************
* Copyright (c) 2015-2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
* Copyright (c) 2013 Nikita Mikhaylov <nslqqq@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the
* Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************/

#ifndef GREETERAPP_H
#define GREETERAPP_H

#include <QObject>
#include <QScreen>
#include <QQuickView>
#include <QOpenGLFramebufferObject>
#include <QScopedPointer>

class QTranslator;

namespace SDDM {
    class Configuration;
    class ThemeMetadata;
    class ThemeConfig;
    class SessionModel;
    class ScreenModel;
    class UserModel;
    class GreeterProxy;
    class KeyboardModel;


    class GreeterApp : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(GreeterApp)
    public:
        explicit GreeterApp(QObject *parent = nullptr);

        QString themePath() const;
        void setThemePath(const QString &path);
        QString screeshotPath() const;
        void setScreeshotPath (const QString &path);
        void screenshot();
        void screenshot(QQuickView *view);
        void screenshot(QScreen *screen);

    protected:
        void customEvent(QEvent *event) override;

    private slots:
        void addViewForScreen(QScreen *screen);
        void removeViewForScreen(QQuickView *view);

    private:
        QScopedPointer<QOpenGLFramebufferObject> m_fbo;
        bool m_testing = false;
        QString m_socket;
        QString m_themePath;
        QString m_screenshotPath;

        QList<QQuickView *> m_views;
        QTranslator *m_theme_translator { nullptr },
                    *m_components_tranlator { nullptr };

        ThemeMetadata *m_metadata { nullptr };
        ThemeConfig *m_themeConfig { nullptr };
        SessionModel *m_sessionModel { nullptr };
        UserModel *m_userModel { nullptr };
        KeyboardModel *m_keyboard { nullptr };

        void startup();
        void activatePrimary();
    };

    class StartupEvent : public QEvent
    {
    public:
        StartupEvent();
    };
}


#endif // GREETERAPP_H
