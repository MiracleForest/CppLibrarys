#pragma once
#include "EAppControl.h"

class krnl_ShapeBox:public EAppControl
{
protected:
	void 取控件默认附加属性(QHash<QString, QVariant>& out_data);
	void 反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void 显示控件属性信息(QHash<QString, QVariant>& out_data);
	qstring 取事件名称(int eventIndex);
	QString 取图标资源路径();
private:
	static QStringList 取外形列表();
	static QStringList 取线条效果列表();
	static QStringList 取线型列表();
};