#include <QtGui>

#include "Cell.h"

Cell::Cell()
{
	setDirty();
}

QVariant Cell::data(int role) const
{
	if (role == Qt::DisplayRole) {
		if (value().isValid()) {
			return value().toString();
		} else {
			return "####";
		}
	} else if (role == Qt::TextAlignmentRole) {
		if (value().type() == QVariant::String) {
			return int(Qt::AlignLeft | Qt::AlignVCenter);
		} else {
			return int(Qt::AlignRight | Qt::AlignVCenter);
		}
	}	else {
		return QTableWidgetItem::data(role);
	}
}

void Cell::setData(int role, const QVariant& value)
{
	QTableWidgetItem::setData(role, value);
	if (role == Qt::EditRole)
		setDirty();
}

QTableWidgetItem* Cell::clone()const
{
	return new Cell(*this);
}

void Cell::setFormula(const QString& formula)
{
	setData(Qt::EditRole, formula);
}

QString Cell::formula()const
{
	return data(Qt::EditRole).toString();
}