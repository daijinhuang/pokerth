/*****************************************************************************
 * PokerTH - The open source texas holdem engine                             *
 * Copyright (C) 2006-2011 Felix Hammer, Florian Thauer, Lothar May          *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU Affero General Public License as            *
 * published by the Free Software Foundation, either version 3 of the        *
 * License, or (at your option) any later version.                           *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU Affero General Public License for more details.                       *
 *                                                                           *
 * You should have received a copy of the GNU Affero General Public License  *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************/
#ifndef MYGAMELISTSORTFILTERPROXYMODEL_H
#define MYGAMELISTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MyGameListSortFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT

public:
	MyGameListSortFilterProxyModel(QObject *parent = 0);
	void setColumn1RegExp(QRegExp column1) {
		column1RegExp = column1;
	}
	void setColumn2RegExp(QRegExp column2) {
		column2RegExp = column2;
	}
	void setColumn3RegExp(QRegExp column3) {
		column3RegExp = column3;
	}
	void setColumn4RegExp(QRegExp column4) {
		column4RegExp = column4;
	}

protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
	QRegExp column1RegExp;
	QRegExp column2RegExp;
	QRegExp column3RegExp;
	QRegExp column4RegExp;

};

#endif // MYGAMELISTSORTFILTERPROXYMODEL_H
