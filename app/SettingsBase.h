/***************************************************************************
 *   Copyright (C) 2009 by Ben Cooksley <bcooksley@kde.org>                *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA          *
 ***************************************************************************/

#ifndef SETTINGS_BASE_H
#define SETTINGS_BASE_H

#include "BaseMode.h"
#include "MenuItem.h"
#include "tooltipmanager.h"
#include "ui_configDialog.h"

#include <QButtonGroup>
#include <QMap>
#include <QStackedWidget>

#include <KAboutApplicationDialog>
#include <KActionMenu>
#include <KConfigDialog>
#include <KLineEdit>
#include <KService>
#include <KXmlGuiWindow>

class SettingsBase : public KXmlGuiWindow
{
    Q_OBJECT

public:
    explicit SettingsBase(BaseMode::ApplicationMode mode, QWidget *parent = nullptr);
    ~SettingsBase() override;
    bool queryClose() override;

    void setStartupModule(const QString &startupModule);
    void setStartupModuleArgs(const QStringList &startupModuleArgs);
    void reloadStartupModule();

protected:
    QSize sizeHint() const override;

private Q_SLOTS:
    void initApplication();
    void initToolBar();
    void initHelpMenu();
    void initConfig();
    void initMenuList(MenuItem *parent);
    void configUpdated();
    void configShow();
    void about();
    void changePlugin();
    void viewChange(bool state);
    void updateViewActions();
    void changeToolBar(BaseMode::ToolBarItems toolbar);
    void changeAboutMenu(const KAboutData *menuAbout, QAction *menuItem, const QString &fallback);

private:
    // The plugins
    QMap<QString, BaseMode *> possibleViews;
    QList<ToolTipManager *> tooltipManagers;
    BaseMode *activeView = nullptr;
    // The search bar
    KLineEdit *searchText = nullptr;
    QWidget *spacerWidget = nullptr;
    // The toolbar
    QWidgetAction *searchAction = nullptr;
    QWidgetAction *spacerAction = nullptr;
    QAction *configureAction = nullptr;
    QAction *quitAction = nullptr;
    // The help menu
    QAction *aboutViewAction = nullptr;
    QAction *aboutModuleAction = nullptr;
    KActionMenu *helpActionMenu = nullptr;
    // The configuration
    KConfigDialog *configDialog = nullptr;
    Ui::ConfigDialog configWidget;
    QButtonGroup viewSelection;
    // The control module
    QStackedWidget *stackedWidget = nullptr;
    // The module list
    MenuItem *rootModule = nullptr;
    MenuItem *homeModule = nullptr;
    MenuItem *lostFound = nullptr;
    KService::List categories;
    KService::List modules;
    // The about dialog
    KAboutApplicationDialog *aboutDialog = nullptr;
    BaseMode::ApplicationMode m_mode = BaseMode::SystemSettings;
    QString m_startupModule;
    QStringList m_startupModuleArgs;
};
#endif
