#include "Spreadsheet.h"



Spreadsheet::Spreadsheet(QWidget *parent)
	:QTableWidget(parent)
{

};

Cell* Spreadsheet::cell(int row, int colunm)const
{

}

QString Spreadsheet::formula(int raw, int colum) const
{
	Cell* c = cell(row, column);
}

QString Spreadsheet::currentLocation()const
{
	return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const
{
	return formula(currentRow(), currentColumn());
}