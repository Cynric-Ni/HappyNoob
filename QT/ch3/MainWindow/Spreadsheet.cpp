#include "Spreadsheet.h"
#include <QtGui>
#include <QtCore>
#include <QtWidgets>


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

bool Spreadsheet::readFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, tr("Spreadshtte"),
			tr("Cannot read file %1:\n%2.")
			.arg(file.fileName())
			.arg(file.errorString()));
		return false;
	}

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_6_2);

	quint32 magic;
	in >> magic;
	if (magic != MagicNumber) {
		QMessageBox::warning(this, tr("Spreadsheet"),
			tr("The file is not a Spreadsheet file."));
		return false;
	}

	clear();

	quint16 row;
	quint16 column;
	QString str;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	while (!in.atEnd()) {
		in >> row >> column >> str;
		setFormula(row, column, str);
	}
	QApplication::restoreOverrideCursor();
	return true;
}

QTableWidgetSelectionRange Spreadsheet::selectedRange()const
{
	QList<QTableWidgetSelectionRange> ranges = selectedRanges();
	if (ranges.isEmpty())
		return QTableWidgetSelectionRange();
	return ranges.first();
}

void Spreadsheet::sort(const SpreadsheetCompare& compare)
{
	QList<QStringList> rows;
	QTableWidgetSelectionRange range = selectedRange();

}

bool SpreadsheetCompare::operator()(const QStringList& row1,
	                               const QStringList& row2) const
{
	for (int i = 0; i < KeyCount; ++i) {
		int column = keys[i];
		if (column != -1) {
			if (row1[column] != row2[column]) {
				if (ascending[i]) {
					return row1[column] < row2[column];
				} else {
					return row1[column] > row2[column];
				}

			}
		}
	}
	return false; 
}