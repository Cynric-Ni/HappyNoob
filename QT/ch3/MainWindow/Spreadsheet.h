#pragma once
#include <QTableWidget>

class Cell;
class SpreadsheetCompare;


class Spreadsheet :public  QTableWidget
{
	Q_OBJECT
public:
	Spreadsheet(QWidget *parent = 0);

	bool autoRecalculate() const { return autoRecalc; }
	QString currentLocation() const;
	QString currentFormula() const;
	bool readFile(const QString& fileName);
	bool writeFile(const QString& fileName);
	QTableWidgetSelectionRange selectedRange()const;
	void clear();
	void sort(const SpreadsheetCompare &compare);
private:
	enum{MagicNumber = 0x7F51C883,};
	Cell* cell(int row, int column) const;
	QString text(int row, int column)const;
	QString formula(int row, int column) const;
	void setFormula(int row, int column,const QString &formula) const;

	bool autoRecalc;
public slots:
    void cut();
    void copy();
    void paste();
    void del();
	void selectCurrentRow();
	void selectCurrentColumn();
	void recalculate();
	void setAutoRecalculate(bool recalc);
	void findNext(const QString& str, Qt::CaseSensitivity cs);
private:
	enum { MagicNumber = 0x7F51C883, RowCount = 999,ColumnCount = 26};
signals:
	void modified();

private slots:
	void somethingChanged();
};

class SpreadsheetCompare
{
public:
	bool operator()(const QStringList& row1,
		const QStringList& row2) const;
	enum { KeyCount = 3 };
	int keys[KeyCount];
	bool ascending[KeyCount];
};