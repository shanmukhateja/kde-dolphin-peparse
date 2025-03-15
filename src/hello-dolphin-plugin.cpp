#include <QWidget>
#include <QObject>
#include <QString>
#include <KPluginFactory>

#include <kpluginfactory.h>

#include <KFileItem>

#include "hello-dolphin-plugin.h"


HelloDolphinPlugin::HelloDolphinPlugin(QObject *parent) : KPropertiesDialogPlugin(parent)
{
    qInfo() << "Hello world from HelloDolphinPlugin";
    this->init();
}

void HelloDolphinPlugin::init()
{
    qInfo() << this->properties->items().size();
    if (this->properties->items().size() == 1) {
        QString fileName = this->properties->item().url().fileName();
        if (fileName.endsWith(QString::fromUtf8(".exe"))) {
            qInfo() << "Valid EXE file";
        }
    }
}


K_PLUGIN_CLASS_WITH_JSON(HelloDolphinPlugin, "hello-dolphin-plugin.json")


// MOC file
#include "hello-dolphin-plugin.moc"

