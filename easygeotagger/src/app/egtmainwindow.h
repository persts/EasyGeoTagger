/*
** File: egtmainwindow.h
** Author( s ): Peter J. Ersts ( ersts at amnh.org )
** Creation Date: 2008-09-22
**
** Copyright ( c ) 2008-2009, American Museum of Natural History. All rights reserved.
** 
** This library/program is free software; you can redistribute it 
** and/or modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or ( at your option ) any later version.
** 
** This library/program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.
**
** This work was made possible through a grant by the the John D. and 
** Catherine T. MacArthur Foundation with additional support from the 
** Center For Biodiversity and Conservation and The Spanish Ministry of 
** Science and Innovation's INTEGRANTS program.
**
**/
#ifndef EGTMAINWINDOW_H
#define EGTMAINWINDOW_H

#include "ui_egtmainwindowgui.h"

#include "egtpathbuilder.h"
#include "egtimagefactory.h"
#include "egtphotoexifengine.h"

#include <QWebView>
#include <QToolBox>
#include <QFileInfo>
#include <QMainWindow>
#include <QModelIndex>
#include <QDockWidget>

namespace Ui
{
    class EgtMainWindowGui;
}

/*! \brief Main EasyGeoTagger window
 *
 */
class MS_DLL_SPEC EgtMainWindow : public QMainWindow
{

  Q_OBJECT
  
public:
  /*! \brief Constructor */
  EgtMainWindow( QWidget* theParent = 0 );
  
  /*! \brief Set the plugin dock's tool box */
  void setPluginToolBox( QToolBox* );

public slots:
  /*! \brief Accept refresh requests for the file browser from the application interface */
  void refreshFileBrowser( );

private slots:
  /*! \brief Slot to listen for mouse in the file browser */
  void clicked( const QModelIndex& );

  /*! \brief Slot to show the preview */
  void loadPreview( bool );  

  /*! \brief Slot for menu about action */
  void on_actionAbout_activated( );

  /*! \brief Slot for menu exit action */
  void on_actionExit_activated( );

  /*! \brief Slot for menu load plugin action */
  void on_actionLoadAll_activated( );

  /*! \brief Slot for menu load plugin action */
  void on_actionLoadSingle_activated( );

  /*! \brief Slot to interact with the progress bar */
  void updateProgress( int, int, int );

signals:
  /*! \brief Signal to broadcast a mouse click event in the file browser */
  void fileBrowserItemSelected( const QModelIndex& );

  /*! \brief Sugnal to broadcast a load plugin request */
  void loadPlugins( QString );

  
private:
  QFileInfo cvFileInfo;
  EgtImageFactory cvImageFactory;
  EgtPathBuilder cvPathBuilder;
  EgtPhotoExifEngine cvPhotoExifEngine;
  QDockWidget* cvPluginDock;
  Ui::EgtMainWindowGui* cvUi;
  QWebView cvWebBrowser;
};
#endif
