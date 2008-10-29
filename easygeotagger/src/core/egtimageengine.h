/*
** File: egtimageengine.h
** Author(s): Roberto Garcia Yunta, Peter J. Ersts (ersts at amnh.org)
** Creation Date: 2008-10-07
**
** Copyright (c) 2008, American Museum of Natural History. All rights reserved.
** 
** This library/program is free software; you can redistribute it 
** and/or modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
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
#ifndef EGTIMAGEENGINE_H
#define EGTIMAGEENGINE_H

#include "libraw/libraw.h"
#include "egtrawthread.h"
#include <QImage>
#include <QModelIndex>

class MS_DLL_SPEC EgtImageEngine : public QObject
{ 
  Q_OBJECT 
  
  public:
    /*! \brief Constructor */
    EgtImageEngine( );
    
    /*! \brief Constructor */
    EgtImageEngine( QString );
    
    /*! \brief Destructor */
    ~EgtImageEngine();
    
    /*! \brief Returns the a copy of the current resize image */
    QImage scaledImage( bool* isValid=0 );
    
    /*! \brief Returns a copy of the image resized to the specified dimensions */
    QImage scaleImage( int, int, bool* isValid=0 );
  
    /*! \brief Set the image filename */
    void setFile( QString );
    
    /*! \brief Save the current resized image as a jpeg */
    bool saveAsJpeg( QString );
  
  private:
    /*! \brief Initialization steps */
    void init();
    
    /*! \brief Open the raw image file do everything but read the image data */
    bool preprocessRaw( QString );
    
    /*! \brief Read/open the base image as a jpeg */
    void readJpeg( QString );
    
    /*! \brief Read/open the base image as a raw image format */
    void readRaw( QString );
    
    /*! \brief Read/open the base image as a tiff */
    void readTiff( QString );
    
    
    /*! \brief Has the base image been resized */
    bool cvHasBeenResized;
    
    /*! \brief Has a valid thumbnail image */
    bool cvHasThumbnail;
    
    /*! \brief Was the last image opened sucessfully */
    bool cvIsValidImage;    
    
    /*! \brief Raw image processor */
    LibRaw cvRawProcessor;
    
    /*! \brief Local copy of the current resized image */
    QImage cvResizedImage;
    
    /*! \brief QImage containing the original/base image data */
    QImage* cvOriginalImage;
    
    /*! \brief QImage containing embeded thumbnail for raw images */
    QImage cvThumbnailImage;

    EgtRawThread* cvRawThread;

bool cvIsProcessing;


  
  signals:
    void progress( int, int, int );
    void imageLoaded(bool);

  private slots:
  /*! \brief Slot to re-emit the progress to the main window which has the progress bar */
  void reEmitProgress( int, int, int );
  void threadComplete( bool );

};
#endif
