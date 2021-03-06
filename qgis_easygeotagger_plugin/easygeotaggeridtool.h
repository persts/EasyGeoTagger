/*
** File: easygeotaggeridtool.h
** Author( s ): Peter J. Ersts ( ersts at amnh.org )
** Creation Date: 2008-10-20
**
** Copyright ( c ) 2008, American Museum of Natural History. All rights reserved.
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
#ifndef EASYGEOTAGGER_H
#define EASYGEOTAGGER_H

#include <QMouseEvent>
#include <QWidget>

#include "qgspoint.h"
#include "qgsmaptool.h"
#include "qgsmapcanvas.h"
#include "qgsmaplayer.h"
#include "qgscoordinatereferencesystem.h"

/*!
* \class EasyGeoTaggerIdTool
* \brief Map tool for collecting mouse clicks
*
* The EasyGeoTaggerIdTool is an id style map tool that is used to select point and send them back to the EasyGeoTagger
* application
*/
class EasyGeoTaggerIdTool : public QgsMapTool
{
  Q_OBJECT
  
  public:
    /*! \brief Constructor */
    EasyGeoTaggerIdTool( QgsMapCanvas* );
    
    /*! \brief Method to handle mouse release, i.e., select, event */
    void canvasReleaseEvent( QMouseEvent* );

  signals:
    void keyValuePair( QString, QString );
    
  private:
    /*! \brief The destination CRS for transforming points */
    QgsCoordinateReferenceSystem* cvDestinationCRS;
};
#endif
