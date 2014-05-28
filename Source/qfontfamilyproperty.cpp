#include "stdafx.h"
#include "qfontfamilyproperty.h"

QString QFontFamilyProperty::QualifiedVariantPropertyName = "QFont::Family";

QFontFamilyProperty::QFontFamilyProperty(const QString& propertyName, int propertyIndex, const QVariant& value, QVariantProperty *parent)
	:QVariantProperty(value, QMetaProperty(), parent)
{
	this->propertyName = propertyName;
	this->rowInParent = propertyIndex;
}

QFontFamilyProperty::~QFontFamilyProperty()
{

}

QVariant QFontFamilyProperty::getData(Qt::ItemDataRole role , Column column)
{
	switch (column)
	{
	case QVariantProperty::PropertyNameColumn:
		switch (role)
		{
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return QVariant();
			break;
		case Qt::DisplayRole:
		case Qt::ToolTipRole:
		case Qt::StatusTipRole:
		case Qt::WhatsThisRole:
			{
				return propertyName;
			}
			break;
		case Qt::FontRole:
			return QVariant();
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QVariant();
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}

		break;
	case QVariantProperty::PropertyValueColumn:
		switch (role)
		{
		case Qt::DisplayRole:
			{
				QFont temp = qvariant_cast<QFont>(value);
				QString name = "[" + temp.family() +"]";
				return name;
			}
			break;
		case Qt::DecorationRole:
			return QVariant();
			break;
		case Qt::EditRole:
			return value;
			break;
		case Qt::ToolTipRole:
			return QVariant();
			break;
		case Qt::StatusTipRole:
			return QVariant();
			break;
		case Qt::WhatsThisRole:
			return QVariant();
			break;
		case Qt::FontRole:
			return value;
			break;
		case Qt::TextAlignmentRole:
			return QVariant();
			break;
		case Qt::BackgroundRole:
			return QVariant();
			break;
		case Qt::ForegroundRole:
			return QVariant();
			break;
		case Qt::CheckStateRole:
			return QVariant();
			break;
		case Qt::AccessibleTextRole:
			return QVariant();
			break;
		case Qt::AccessibleDescriptionRole:
			return QVariant();
			break;
		case Qt::SizeHintRole:
			return QVariant();
			break;
		case Qt::InitialSortOrderRole:
			return QVariant();
			break;
		}

		break;
	}

	return QVariant();
}

QString QFontFamilyProperty::getQualifiedVariantPropertyName() const
{
	return "QFont::Family";
}