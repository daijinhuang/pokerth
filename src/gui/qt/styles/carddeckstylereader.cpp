/***************************************************************************
 *   Copyright (C) 2006 by Felix Hammer   *
 *   f.hammer@web.de   *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "carddeckstylereader.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>


using namespace std;

CardDeckStyleReader::CardDeckStyleReader(ConfigFile *c, gameTableImpl *w) : myConfig(c), myW(w), fallBack(0)
{
	
}


CardDeckStyleReader::~CardDeckStyleReader()
{
}

void CardDeckStyleReader::readStyleFile(QString file) {

	string tinyFileName;

	//if style file failed --> default style fallback
	if(QFile(file).exists()) { 
		currentFileName = QFile(file).fileName();
		tinyFileName = currentFileName.toUtf8().constData();		 
	}
	else { 
		currentFileName = QFile(QString::fromUtf8(myConfig->readConfigString("AppDataDir").c_str())+"gfx/cards/default/defaultdeckstyle.xml").fileName(); 
		tinyFileName = currentFileName.toUtf8().constData(); 
		fallBack = 1;
	}
	QFileInfo info(currentFileName);
	currentDir = info.absolutePath()+"/";

	//start reading the file and fill vars	
	string tempString1("");
	TiXmlDocument doc(tinyFileName); 
		
	if(doc.LoadFile()) {
		TiXmlHandle docHandle( &doc );	
	
		TiXmlElement* itemsList = docHandle.FirstChild( "PokerTH" ).FirstChild( "CardDeck" ).FirstChild().ToElement();
		for( ; itemsList; itemsList=itemsList->NextSiblingElement()) {
			const char *tmpStr1 = itemsList->Attribute("value");
			if (tmpStr1) {
				tempString1 = tmpStr1;

				if(itemsList->ValueStr() == "StyleDescription") { StyleDescription = QString::fromUtf8(tempString1.c_str()); }
				else if(itemsList->ValueStr() == "StyleMaintainerEMail") { StyleMaintainerEMail = QString::fromUtf8(tempString1.c_str()); }
				else if (itemsList->ValueStr() == "Preview") { Preview = currentDir+QString::fromUtf8(tempString1.c_str()); }
			}
		}
		
	}
	else {	qDebug() << "could not load card deck file: " << tinyFileName.c_str(); }

	//check if all files are there
	cardsLeft.clear();
	int i;
	for(i=0; i<52; i++) {
		QString cardString(QString::number(i)+".png");
		if(!QDir(currentDir).exists(cardString)) {
			cardsLeft << cardString;
		}
	}
	if(!QDir(currentDir).exists("flipside.png")) {
			cardsLeft << "flipside.png";
	}
	
	if(!cardsLeft.isEmpty() && myW != 0) showErrorMessage(StyleDescription, cardsLeft, StyleMaintainerEMail);
}

void CardDeckStyleReader::showErrorMessage(QString style, QStringList failedItems, QString email)
{
	QString items = failedItems.join(", ");

	QMessageBox::warning(myW, tr("Card Deck Style Error"),
                                tr("Selected card deck style \"%1\" seems to be incomplete or defective. \nThe card picture(s) \"%2\" is/are not available. \n\nPlease contact the card deck style builder %3.").arg(style).arg(items).arg(email),
                                QMessageBox::Ok);
}