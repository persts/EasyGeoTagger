/*
** File: 
** Author(s): 
** Creation Date: 
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
#include "egtgpsdatatablewidget.h"

#include <QVBoxLayout>


EgtGpsDataTableWidget::EgtGpsDataTableWidget( )
{
  setRowCount(10);
  setColumnCount(3);

  QStringList lvTags;
  lvTags << "Longitude" << "Latitude" << "Altitude";
  setHorizontalHeaderLabels(lvTags);

  cvMapItems = new QMap<QString,QString>;

  //Populate the table with some data
  populateTable();

  connect( this, SIGNAL( cellClicked(int, int) ), this, SLOT( cell_selected(int, int) ) );  

  cvHorizontalHeader = horizontalHeader();
  connect( cvHorizontalHeader, SIGNAL( sectionClicked( int ) ), this, SLOT( cvHorizontalHeader_clicked(int) ) ); 

  cvVerticalHeader = verticalHeader();
  connect( cvVerticalHeader, SIGNAL( sectionClicked( int ) ), this, SLOT( cvVerticalHeader_clicked(int) ) ); 
}

/*
 *
 * PUBLIC FUNCTIONS
 *
 */

QMap<QString,QString>* EgtGpsDataTableWidget::getRowItems()
{
  return cvMapItems;
}

/*
 *
 * PRIVATE FUNCTIONS
 *
 */

void EgtGpsDataTableWidget::populateTable()
{
  for( int lvRowCounter= 0; lvRowCounter<10; lvRowCounter++ )
    for( int lvColumnCounter= 0; lvColumnCounter<3; lvColumnCounter++ )
    {
      QTableWidgetItem *lvNewItem = new QTableWidgetItem(tr("%1").arg(
         (lvRowCounter+1)*(lvColumnCounter+1)));
       setItem( lvRowCounter, lvColumnCounter, lvNewItem );
    }
}
/*
 *
 * SIGNAL and SLOTS
 *
 */

void EgtGpsDataTableWidget::cvHorizontalHeader_clicked( int theIndex )
{
qDebug(("Horizontal header clicked: "+QString::number(theIndex)).toStdString().c_str());
}

void EgtGpsDataTableWidget::cvVerticalHeader_clicked(int theIndex)
{ 
  delete cvMapItems;
  cvMapItems = new QMap<QString,QString>;
 
  QTableWidgetItem* lvHeaderItem;
  for(int lvColumnCount = 0; lvColumnCount < columnCount(); lvColumnCount++)
  {
    QString lvText;
    lvHeaderItem = horizontalHeaderItem ( lvColumnCount );
    lvText = lvHeaderItem->text();
    cvMapItems->insert( lvText, item( theIndex, lvColumnCount )->text() );
  } 
}


void EgtGpsDataTableWidget::cell_selected(int row, int column)
{ 
  QTableWidgetItem * lvItem =item ( row, column );
  double x = lvItem->data(0).toDouble();
  qDebug(("Cell clicked: "+QString::number(x)).toStdString().c_str());
}



/*void EgtGpsDataTableWidget::void setFileReader()
{
}*/
