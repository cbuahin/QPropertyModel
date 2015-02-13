#ifndef QSELECTFROMLISTPROPERTYITEMEDITOR_H
#define QSELECTFROMLISTPROPERTYITEMEDITOR_H


#include "qbasepropertyitemeditor.h"
#include <QComboBox>

class QSelectFromListPropertyItemEditor : public QBasePropertyItemEditor
{
	Q_OBJECT

public:
	QSelectFromListPropertyItemEditor(QWidget *parent);
	~QSelectFromListPropertyItemEditor();

	virtual void setValue(const QVariant& value) Q_DECL_OVERRIDE;

	virtual QVariant getValue() const Q_DECL_OVERRIDE;

private:
	void setUpChildWidget() Q_DECL_OVERRIDE;

private slots:
	void onCurrentIndexChanged(int index);
	//void onCurrentIndexChanged(const QString & text);

private:
	QComboBox* m_comboBox;
	QStringList m_fontFamily;
	bool isEnum;
	QMetaEnum m_metaEnum;
};

#endif // QSELECTFROMLISTPROPERTYITEMEDITOR_H
