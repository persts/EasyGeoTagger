/*
** File: egtgpsdatatable.cpp
** Author( s ): Roberto Garcia Yunta, Peter J. Ersts ( ersts@amnh.org )
** Creation Date: 2008-12-19
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
#include "egtgpsdatatable.h"
#include "egtlogger.h"

#include <QHeaderView>
#include <QMessageBox>
#include <QMenu>
#include <QDate>

EgtGpsDataTable::EgtGpsDataTable( )
{
  cvHeaderSelectionDialog = new QDialog( this );
  cvUiKeySelectionDialog.setupUi( cvHeaderSelectionDialog );

  cvAvailableFields << tr( "( clear )" ) << tr( "Date Time Stamp" );
  QList< EgtExifEngine::KeyMap > lvKeyMap = cvExifEngine.keys();
  QList< EgtExifEngine::KeyMap >::iterator lvIterator = lvKeyMap.begin();
  while( lvIterator != lvKeyMap.end() )
  {
      cvAvailableFields << lvIterator->commonName;
      lvIterator++;
  }


  cvDataProvider = 0;
  cvColumnSelected = 0;
  cvOffset= 0;

  connect( horizontalHeader( ), SIGNAL( sectionClicked( int ) ), this, SLOT( horizontalHeader_clicked( int ) ) );

  verticalHeader()->setContextMenuPolicy(Qt::CustomContextMenu); //to enable the customContextMenuRequested signal
  connect( verticalHeader(), SIGNAL( customContextMenuRequested(QPoint) ), this, SLOT( popUpMenu( QPoint ) ) );
  connect( verticalHeader(), SIGNAL( sectionClicked( int ) ), this, SLOT( verticalHeader_clicked( int ) ) );

  connect( this, SIGNAL( cellClicked( int, int ) ), this, SLOT( cell_selected( int, int ) ) );
  connect( cvUiKeySelectionDialog.pbtnOk, SIGNAL( clicked( ) ), this, SLOT( on_pbtnOk_clicked( ) ) );
}

/*
 *
 * PUBLIC FUNCTIONS
 *
 */

bool EgtGpsDataTable::clearColumnHeader( int theColumn )
{
  return setColumnHeader( theColumn, tr( "( clear )" ) );
}

QMap<QString,QString> EgtGpsDataTable::getRow( )
{
  EgtDebug( "entered" );

  if( !validDateTimeStamp() )
  {
    QMap< QString, QString > lvTemp;
    return lvTemp;
  }

  return cvRowData;
}

QMap<QString,QString> EgtGpsDataTable::getRow( int theRow )
{
  EgtDebug( "entered" );

  selectRow( theRow );

  return cvRowData;
}

bool EgtGpsDataTable::isAnyColumnHeaderSet( )
{
  EgtDebug( "entered" );

  return ( cvColumnHeadersSet.size() > 0 );
}

bool EgtGpsDataTable::hasColumnHeader( QString theFieldName )
{
   for( int lvIterator = 0; lvIterator < columnCount(); lvIterator++ )
   {
     QTableWidgetItem* lvCurrentHeader = horizontalHeaderItem ( lvIterator );
     if( 0 == lvCurrentHeader->text( ).compare( theFieldName, Qt::CaseInsensitive ) )
     {
       return true;
     }
   }

   return false;
}

bool EgtGpsDataTable::setColumnHeader( int theColumn, QString theHeader )
{
  if( theColumn < 0 || theColumn > columnCount() ) { return false; }

  QString lvTheHeader = theHeader;
  if( hasColumnHeader( lvTheHeader ) )
  {
   return false;
  }

  if( tr( "( clear )" ) == lvTheHeader )
  {
    if( cvDataProvider->hasColumnHeaders( ) )
    {//revert to the original header
      lvTheHeader = cvDataProvider->columnHeaders( ).at( theColumn );
    }
    else
    {
      lvTheHeader = QString::number( theColumn +1 );
    }

    cvColumnHeadersSet.remove( theColumn );
  }
  else
  {
    cvColumnHeadersSet << theColumn;
    if( tr( "Date Time Stamp" ) == lvTheHeader )
    {
      emit timeStampSelected( true );
    }
    else
    {
      emit timeStampSelected( false );
    }
  }

  //Deleting the previous header
  QTableWidgetItem* lvCurrentHeader = horizontalHeaderItem ( theColumn );
  if( 0 != lvCurrentHeader )
  {
    delete lvCurrentHeader;
  }

  setHorizontalHeaderItem( theColumn, new QTableWidgetItem( lvTheHeader ) );
}

/*
 *
 * SIGNAL and SLOTS
 *
 */
void EgtGpsDataTable::broadcastRow( )
{
  EgtDebug( "entered" );

  if( isAnyColumnHeaderSet( ) )
  {
    if( !validDateTimeStamp() )
    {
      EgtDebug( "DateTimeStamp was not valid " );
      return;
    }

    QMapIterator<QString, QString> lvMapIterator( cvRowData );
    while ( lvMapIterator.hasNext( ) )
    {
      lvMapIterator.next( );
      if(lvMapIterator.key( ) == tr( "Date Time Stamp" ))
      {
        QDateTime lvDateTime = applyOffset( lvMapIterator.value() );
        if( lvDateTime.isValid() )
        {
            emit( keyValuePair( "Egt.GPS.TimeStamp", lvDateTime.toString( "hh:mm:ss" ) ) );
            emit( keyValuePair( "Egt.GPS.DateStamp", lvDateTime.toString( "yyyy:MM:dd" ) ) );
        }
      }
      else
      {
        emit( keyValuePair( cvExifEngine.key( lvMapIterator.key( ) ),lvMapIterator.value( ) ) );
      }

    }
  }
}

void EgtGpsDataTable::broadcastRow( int theRow )
{
  selectRow( theRow );
  broadcastRow();
}

void EgtGpsDataTable::cell_selected( int row, int column )
{ 
  EgtDebug( "entered" );

  QTableWidgetItem * lvItem = item ( row, column );
  double x = lvItem->data( 0 ).toDouble( );
  emit rowSelected(false);
}

void EgtGpsDataTable::horizontalHeader_clicked( int theIndex )
{
  EgtDebug( "entered" );

  cvColumnSelected = theIndex;
  cvHeaderSelectionDialog->show( );
  emit rowSelected( false );
}

void EgtGpsDataTable::deleteRow()
{ 
  EgtDebug( "entered" );
  deleteRow( cvSelectedRow );
}

void EgtGpsDataTable::deleteRow( int theRow )
{
  EgtDebug( "entered" );
  if( rowCount() != 0 &&  ( theRow >= 0 || theRow < rowCount() ) )
  {
    removeRow( theRow );
    cvSelectedRow = -1;
    emit rowSelected( false );
  }
}

void EgtGpsDataTable::on_pbtnOk_clicked( )
{  
  EgtDebug( "entered" );
  QString lvHeader = cvUiKeySelectionDialog.cbFields->currentText( );

  if( hasColumnHeader( lvHeader ) )
  {
    QMessageBox::critical( this, tr( "Error" ),tr( "Another column has already been set to") + ":" + lvHeader,QMessageBox::Ok );
    return;
  }

  setColumnHeader( cvColumnSelected, lvHeader );
  
  cvHeaderSelectionDialog->close( );
}

void EgtGpsDataTable::popUpMenu(QPoint theCoordinates)
{
  EgtDebug( "entered" );

  QMenu menu;
  QAction* lvDeleteAction = new QAction( tr("&Delete row..."), this );
  lvDeleteAction->setStatusTip(tr("Delete the selected row"));
  cvSelectedRow = verticalHeader()->logicalIndexAt( theCoordinates );
  connect( lvDeleteAction, SIGNAL( triggered() ), this, SLOT( deleteRow() ) );
     
  menu.addAction(lvDeleteAction);

  menu.exec(mapToGlobal(theCoordinates));
}

void EgtGpsDataTable::selectRow( int theRow )
{
  EgtDebug( "entered" );

  cvRowData.clear();
  cvSelectedRow = -1;
  if( theRow < 0 || theRow > rowCount() )
  {
    emit rowSelected( false );
    return;
  }

  cvSelectedRow = theRow;
  if( isAnyColumnHeaderSet( ) )
  {
    QTableWidgetItem* lvHeaderItem;
    QSet< int >::iterator lvIterator = cvColumnHeadersSet.begin();
    while( lvIterator != cvColumnHeadersSet.end() )
    {
      QString lvHeader;
      lvHeaderItem = horizontalHeaderItem ( *lvIterator );
      lvHeader = lvHeaderItem->text( );
      cvRowData.insert( lvHeader, item( theRow, *lvIterator )->text( ) );
      lvIterator++;
    }
  }

  emit rowSelected(true);
}

void EgtGpsDataTable::setOffset( int theOffset )
{
  EgtDebug( "entered" ); 
 
  EgtDebug( "Offset = " + QString::number( theOffset ) );
  cvOffset = theOffset;
}

void EgtGpsDataTable::setProvider( EgtDataProvider* theProvider )
{
  EgtDebug( "entered" );

  if( 0 != cvDataProvider ) { delete cvDataProvider; }

  cvDataProvider = theProvider;
  populateTable( );
}

void EgtGpsDataTable::verticalHeader_clicked( int theIndex )
{
  selectRow( theIndex );
  if( !validDateTimeStamp() )
  {
    QMessageBox::critical( this, tr( "Error" ),tr( "The date time stamp has an incorrect format.\n The expected format is:\n yyyy:mm:dd hh:mm:ss" ),QMessageBox::Ok );
  }
}

/*
 *
 * PRIVATE FUNCTIONS
 *
 */

QDateTime EgtGpsDataTable::applyOffset( QString theDateTimeStamp )
{
    EgtDebug( "enetered" );

    QDateTime lvNewDateTime = QDateTime::fromString( theDateTimeStamp, "yyyy:MM:dd hh:mm:ss" );
    return lvNewDateTime.addSecs( cvOffset );
}

void EgtGpsDataTable::populateTable( )
{
  EgtDebug( "entered" );

  clear();
  setRowCount( 0 );
  setColumnCount( 0 );

  /*Reset the Qlist that contains which headers are set*/
  cvColumnHeadersSet.clear( );

  if( cvDataProvider == 0 || cvDataProvider->numberOfRecords( ) == 0 || cvDataProvider->numberOfFields( ) == 0 ) { return; }
  cvDataProvider->reset();
  setRowCount( cvDataProvider->numberOfRecords( ) );
  setColumnCount( cvDataProvider->numberOfFields( ) );

  /*Set up the combo box*/
  cvUiKeySelectionDialog.cbFields->clear( );
  cvUiKeySelectionDialog.cbFields->insertItems( 0,cvAvailableFields );

  if( cvDataProvider->hasColumnHeaders( ) )
  {
    QStringList lvTags;
    lvTags = cvDataProvider->columnHeaders( );
    setHorizontalHeaderLabels( lvTags );
  }
  else
  {
    QStringList lvDefaultHeader;

    for( int i = 0; i< cvDataProvider->numberOfFields( ); i++ )
    {
      lvDefaultHeader << QString::number( i+1 );
    }

    setHorizontalHeaderLabels( lvDefaultHeader );
  }

  for( int i = 0; i < cvDataProvider->numberOfRecords( ); i++ )
  {
    QStringList cvRowData = cvDataProvider->next();

    for( int j = 0; j < cvRowData.size( ); j++ )
    {
      QTableWidgetItem *lvNewItem = new QTableWidgetItem( cvRowData.at( j ) );
       setItem( i, j, lvNewItem );
    }
  }
  emit timeStampSelected( false );
  emit rowSelected( false );
}

bool EgtGpsDataTable::validDateTimeStamp()
{
  if( cvRowData.contains( tr( "Date Time Stamp" ) ) )
  {
    EgtDebug( cvRowData[ tr( "Date Time Stamp" ) ] );
    QDateTime lvDateTime = QDateTime::fromString( cvRowData[ tr( "Date Time Stamp" ) ], "yyyy:MM:dd hh:mm:ss" );
    if( !lvDateTime.isValid() )
    {
      return false;
    }
  }

  return true;
}