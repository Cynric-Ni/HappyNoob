#include "iconeditor.h"
#include "iconeditorplugin.h"

#include <QtPlugin>

IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IconEditorPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IconEditorPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IconEditorPlugin::createWidget(QWidget *parent)
{
    return new IconEditor(parent);
}

QString IconEditorPlugin::name() const
{
    return QLatin1String("IconEditor");
}

QString IconEditorPlugin::group() const
{
    return QLatin1String("My Plugins");
}

QIcon IconEditorPlugin::icon() const
{
    return QIcon(":/images/iconeditor.png");
}

QString IconEditorPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IconEditorPlugin::whatsThis() const
{
    return QLatin1String("这个部件是联系5中<i>C++ GUI"
        "Programming with Qt4 </i>里的一个练习自定义Qt部件。");
}

bool IconEditorPlugin::isContainer() const
{
    return false;
}

QString IconEditorPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IconEditor\" name=\"iconEditor\">\n</widget>\n");
}

QString IconEditorPlugin::includeFile() const
{
    return QLatin1String("iconeditor.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin)
#endif // QT_VERSION < 0x050000
