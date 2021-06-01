#pragma once
#include <QTableWidget>


class Spreadsheet :public  QTableWidget
{
	Q_OBJECT
public:
	Spreadsheet(QWidget *parent = 0);

	QString currentLocation() const;
	QString currentFormula() const;
private:
	Cell* cell(int row, int column) const;
	QString formula(int raw, int colum) const;
};