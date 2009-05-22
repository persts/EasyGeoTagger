#include "egtgpxparser.h"

EgtGpxParser::EgtGpxParser()
{
  cvMapGpxElements["ele"] = "Altitude";
  cvMapGpxElements["lon"] = "Longitude";
  cvMapGpxElements["lat"] = "Latitude";
  cvMapGpxElements["time"] = "DateTimeStamp";

  cvElementName = "";
  cvInActualData =false;
}

bool EgtGpxParser::characters ( const QString & ch )
{
  if( cvInActualData && cvElementName!= "" )
  {
    cvRowData.insert( cvHeader.indexOf( cvElementName ), ch );
  }

  return true;
}

QStringList EgtGpxParser::headers()
{
  return cvHeader;
}

QList<QStringList> EgtGpxParser::data()
{
  return cvFileData;
}

bool EgtGpxParser::endElement( const QString&, const QString &localname, const QString &name )
{
  if( 0 == name.compare("wpt", Qt::CaseInsensitive ) || 0 == name.compare("rtept", Qt::CaseInsensitive ) 
      || 0 == name.compare("trkpt", Qt::CaseInsensitive ) )
  {
    cvFileData<<cvRowData; 

    for(int i =0; i < cvRowData.size(); i++){cvRowData[i] = ""; } //reset cvRowData
    cvInActualData = false;
  }
  cvElementName ="";
  return true;
}

int EgtGpxParser::numberOfFields()
{
  return cvHeader.size();
}

void EgtGpxParser::reset()
{
  cvElementName = "";
  cvInActualData = false;
  cvFileData.clear();
  cvHeader.clear();
}

bool EgtGpxParser::startDocument()
{
  return true;
}

bool EgtGpxParser::startElement( const QString&, const QString&, const QString &name, const QXmlAttributes &attrs )
{
  if( 0 == name.compare("wpt", Qt::CaseInsensitive ) || 0 == name.compare("rtept", Qt::CaseInsensitive ) 
      || 0 == name.compare("trkpt", Qt::CaseInsensitive ) )
  {
    for( int i=0; i<attrs.count(); i++ )
    {
      QString lvAttributeName = cvMapGpxElements[ attrs.localName( i ) ];

      if( lvAttributeName!= "" && !cvHeader.contains( lvAttributeName ) ) 
      { 
        cvHeader.append( lvAttributeName ); 
        cvRowData.append("");
      }
      cvRowData.replace( cvHeader.indexOf( lvAttributeName ), attrs.value( i ) );  
    }
    cvInActualData = true; 
  }
  else
  { 
    if(cvInActualData)
    { 
      cvElementName = cvMapGpxElements[ name ]; 
      if( cvElementName!= "" && !cvHeader.contains( cvElementName ) ) { cvHeader.append( cvElementName ); }
    } 
  }

  return true;
}