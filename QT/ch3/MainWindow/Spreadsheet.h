#pragma once
#include <QTableWidget>
#include "Cell.h"


class SpreadsheetCompare
{
public:
	bool operator()(const QStringList& row1,
		const QStringList& row2) const;
	enum { KeyCount = 3 };
	int keys[KeyCount];
	bool ascending[KeyCount];
};

class Spreadsheet :public  QTableWidget
{
	Q_OBJECT
public:
	Spreadsheet(QWidget *parent = 0);

	QString currentLocation() const;
	QString currentFormula() const;
	bool readFile(const QString& fileName);
	QTableWidgetSelectionRange selectedRange()const;
	void sort(const SpreadsheetCompare &compare);
private:
	enum{MagicNumber = 0x7F51C883,};
	Cell* cell(int row, int column) const;
	QString formula(int raw, int colum) const;
	
};

