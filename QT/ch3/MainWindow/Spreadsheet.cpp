#include "Spreadsheet.h"
#include "Cell.h"
#include <QtGui>
#include <QtCore>
#include <QtWidgets>


Spreadsheet::Spreadsheet(QWidget *parent)
	:QTableWidget(parent)
{
	autoRecalc = true;

	setItemPrototype(new Cell);
	setSelectionMode(ContiguousSelection);

	connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
		this, SLOT(somethingChanged()));

	clear();
};

void Spreadsheet::clear()
{
	setRowCount(0);
	setColumnCount(0);
	setRowCount(RowCount);
	setColumnCount(ColumnCount);

	for (int i = 0; i < ColumnCount; ++i) {
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setText(QString(QChar('A' + i)));
		setHorizontalHeaderItem(i, item);
	}
	setCurrentCell(0, 0);
}

Cell* Spreadsheet::cell(int row, int column)const
{
	return static_cast<Cell*>(item(row, column));
}

QString Spreadsheet::text(int row, int column)const
{
	Cell* c = cell(row, column);
		if (c) {
			return c->text();
		} else {
			return "";
		}
}

QString Spreadsheet::formula(int row, int column) const
{
	Cell* c = cell(row, column);
	if (c) {
		return c->formula();
	}
	else {
		return "";
	}
}

void Spreadsheet::setFormula(int row, int column, const QString& formula)
{
	Cell* c = cell(row, column);
	if (!c) {
		c = new Cell;
		setItem(row, column, c);
	}
	c->setFormula(formula);
}

QString Spreadsheet::currentLocation()const
{
	return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

/*QString Spreadsheet::currentFormula() const
{
	return formula(currentRow(), currentColumn());
}*/

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
		//setFormula(row, column, str);
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

/*void Spreadsheet::cut()
{
    copy();
    del();
}

void Spreadsheet::copy()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0)
            str += "\n";
        for (int j = 0; j < range.columnCount(); ++j) {
            if (j > 0)
                str += "\t";
            str += formula(range.topRow() + i, range.leftColumn() + j);
        }
    }
    QApplication::clipboard()->setText(str);
}

void Spreadsheet::paste()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    if (range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows
                || range.columnCount() != numColumns)) {
        QMessageBox::information(this, tr("Spreadsheet"),
                tr("The information cannot be pasted because the copy "
                   "and paste areas aren't the same size."));
        return;
    }

    for (int i = 0; i < numRows; ++i) {
        QStringList columns = rows[i].split('\t');
        for (int j = 0; j < numColumns; ++j) {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if (row < RowCount && column < ColumnCount)
                setFormula(row, column, columns[j]);
        }
    }
    somethingChanged();
}

void Spreadsheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty()) {
        foreach (QTableWidgetItem *item, items)
            delete item;
        somethingChanged();
    }
}*/
