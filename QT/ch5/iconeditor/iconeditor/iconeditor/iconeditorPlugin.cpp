#include "iconeditor.h"
#include "iconeditorPlugin.h"

#include <QtCore/QtPlugin>

iconeditorPlugin::iconeditorPlugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void iconeditorPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool iconeditorPlugin::isInitialized() const
{
    return initialized;
}

QWidget *iconeditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}

QString iconeditorPlugin::name() const
{
    return "iconeditor";
}

QString iconeditorPlugin::group() const
{
    return "My Plugins";
}

QIcon iconeditorPlugin::icon() const
{
    return QIcon(":/images/iconeditor.png");
}

QString iconeditorPlugin::toolTip() const
{
    return QString();
}

QString iconeditorPlugin::whatsThis() const
{
    return QString(tr("这个部件是联系5中<i>C++ GUI"
    "Programming with Qt4 </i>里的一个练习自定义Qt部件。"));
}

bool iconeditorPlugin::isContainer() const
{
    return false;
}

QString iconeditorPlugin::domXml() const
{
    return "<widget class=\"IconEditor\" name=\"iconeditor\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString iconeditorPlugin::includeFile() const
{
    return "iconeditor.h";
}
