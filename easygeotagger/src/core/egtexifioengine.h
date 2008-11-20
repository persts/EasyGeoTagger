/*
** File: egtexifioengine.h
** Author(s): Roberto Garcia-Yunta, Peter J. Ersts (ersts at amnh.org)
** Creation Date: 2008-09-22
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
#ifndef EGTEXIFIOENGINE_H
#define EGTEXIFIOENGINE_H

#include <QModelIndex>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

/*! \brief Read and write EXIF data
 *
 * This class is largely a wrapper for Exiv2 to provide simple access to EXIF header data
 */
class MS_DLL_SPEC EgtExifIoEngine
{

public:
  /*! \brief Constructor */
  EgtExifIoEngine();
  
  /*! \brief Constructor */
  EgtExifIoEngine( QString );
  
  /*! \brief Constructor */
  EgtExifIoEngine( const QModelIndex& );

  double altitude( bool * isValid = 0 );

  QString areaInformation( bool * isValid = 0 );

  QString dateStamp( bool * isValid = 0 );

  float destBearing( bool * isValid = 0 );

  int differential( bool * isValid = 0 );

  float direction( bool * isValid = 0 );

  double destDistance( bool * isValid = 0 );

  double destLatitude( bool * isValid = 0 );

  double destLongitude( bool * isValid = 0 );

  long gpsDOP( bool * isValid = 0 );


  /*! \brief has the image gps exif metadata? */
  bool hasGpsExif();
  
  /*! \brief is the image valid? */
  bool isValidImage();
  
  /*! \brief Returns the last error occured */
  QString lastError(); 

  /*! \brief Returns the latitude */
  double latitude( bool * isValid = 0 );
  
  /*! \brief Returns the longitude */
  double longitude( bool * isValid = 0 );

  QString mapDatum( bool * isValid = 0 );  

  QString measureMode( bool * isValid = 0 );

  QString processingMethod( bool * isValid=0 );

  QString satellites( bool * isValid = 0 );

  /*! \brief Sets the image to be managed with this class */
  void setFile( QString theImageFilename );
  
  double speed( bool * isValid = 0 );

  QString status( bool * isValid = 0 );

  long timeStamp( bool * isValid = 0 );

  float track( bool * isValid = 0 );
 
  int versionID( bool * isValid = 0 );

  /*! \brief writes the latitude from a double number */
  bool writeLatitude(double);
  
  /*! \brief writes the latitude from a QString */
  bool writeLatitude( QString );
  
   /*! \brief writes the longitude from a double */
  bool writeLongitude( double );
  
  /*! \brief writes the longitude from a QString */
  bool writeLongitude( QString );
  
  
  /////////////////////////////////////
bool writeAltitude( double );
bool writeAreaInformation( QString );
bool writeDateStamp( QString);
bool writeDestBearing( float, char theRefference = 'T' );
bool writeDifferential( int );
bool writeDirection( float, char theRefference = 'T' );
bool writeDestDistance( double, char theUnit = 'K' );
bool writeDestLatitude( double, char theRefference = 'N' );
bool writeDestLongitude( double, char theRefference = 'N' );
bool writeGpsDOP( double );
bool writeMapDatum( QString );
bool writeMeasureMode( QString );
bool writeProcessingMethod( QString );
bool writeSatellites( QString );
bool writeSpeed( double, char theUnit = 'K' );
bool writeStatus( QString );
bool writeTimeStamp( long );
bool writeTrack( float, char theRefference = 'T' );
bool writeVersionID( int );
  ////////////////////////////////////



private:
  /*! \brief Converts from decimal degrees to Rational notation */
  QString convertToRational(QString);
  
  /*! \brief reads the value specified as parameter */
  const Exiv2::Value& read(QString);
  
  /*! \brief reads the value specified as parameter and returns it as a QString */
  QString readKeyValueAsString(QString);
  
  /*! \brief writes exif metadata */
  bool write(QString, QString, QString);
  
  /*! \brief has the image GPS exif metadata? */
  bool cvHasGpsExif;

  /*! \brief Exiv2 data to handle the image */
  Exiv2::Image::AutoPtr cvImage;
  
  /*! \brief Name of the file picture */
  QString  cvImageFileName;
  
  /*! \brief is the image valid? */
  bool cvIsValidImage;
  
  /*! \brief Last error occured */
  QString cvLastError;
  
  /*! \brief Exiv2 data used in case we have to work with invalid data */
  Exiv2::DataValue cvNotValidValue;
};
#endif
