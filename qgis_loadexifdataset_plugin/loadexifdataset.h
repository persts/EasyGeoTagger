/***************************************************************************
  loadexifdataset.cpp
  Load EXIF Dataset
  -------------------
         begin                : 2008-09-19
         copyright            : ( C ) Peter J. Ersts 2008
         email                : ersts at amnh.org

 based on plugin template by 

    begin                : Jan 21, 2004
    copyright            : ( C ) 2004 by Tim Sutton
    email                : tim@linfiniti.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *( at your option ) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/*  $Id: plugin.h 9138 2008-08-23 21:37:31Z jef $ */

#ifndef LoadExifDataset_H
#define LoadExifDataset_H

//QT4 includes
#include <QObject>

//QGIS includes
#include "qgisplugin.h"

//forward declarations
class QAction;
class QToolBar;

class QgisInterface;

/**
* \class Plugin
* \brief [name] plugin for QGIS
* [description]
*/
class LoadExifDataset: public QObject, public QgisPlugin
{
    Q_OBJECT
  public:

    //////////////////////////////////////////////////////////////////////
    //
    //                MANDATORY PLUGIN METHODS FOLLOW
    //
    //////////////////////////////////////////////////////////////////////

    /**
    * Constructor for a plugin. The QgisInterface pointer is passed by
    * QGIS when it attempts to instantiate the plugin.
    * @param theInterface Pointer to the QgisInterface object.
     */
    LoadExifDataset( QgisInterface * theInterface );
    //! Destructor
    virtual ~LoadExifDataset( );

  public slots:
    //! init the gui
    virtual void initGui( );
    //! Show the dialog box
    void run( );
    //! unload the plugin
    void unload( );
    //! show the help document
    void help( );
    
    //! slot to propogate draw request
    void draw( QString, QString );

  private:

    ////////////////////////////////////////////////////////////////////
    //
    // MANDATORY PLUGIN PROPERTY DECLARATIONS  .....
    //
    ////////////////////////////////////////////////////////////////////

    int mPluginType;
    //! Pointer to the QGIS interface object
    QgisInterface *mQGisIface;
    //!pointer to the qaction for this plugin
    QAction * mQActionPointer;
    ////////////////////////////////////////////////////////////////////
    //
    // ADD YOUR OWN PROPERTY DECLARATIONS AFTER THIS POINT.....
    //
    ////////////////////////////////////////////////////////////////////
};

#endif //LoadExifDataset_H
