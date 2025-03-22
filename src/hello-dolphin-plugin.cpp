#include <QObject>
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QUrl>

#include <KPluginFactory>
#include <kpluginfactory.h>
#include <KFileItem>
#include <KPageDialog>
#include <KPropertiesDialog>
#include <KSqueezedTextLabel>

#include <regex>

#include "hello-dolphin-plugin.h"
#include "pe-parser-wrapper.h"

using namespace std;

HelloDolphinPlugin::HelloDolphinPlugin(QObject *parent) : KPropertiesDialogPlugin(parent)
{
    this->peWrapper = new PEParserWrapper();
    this->init();
}

void HelloDolphinPlugin::init()
{
    if (this->properties->items().size() == 1)
    {

        QUrl itemUrl = this->properties->item().url();
        QString filePath = itemUrl.path();
        QString fileName = itemUrl.fileName();

        if (this->is_target_file_type(fileName))
        {

            this->version = this->peWrapper->parseFile(filePath);

            if (!this->version.empty())
            {
                // Injects "File Version" details in General tab.
                connect(
                    properties,
                    &KPropertiesDialog::currentPageChanged,
                    this,
                    &HelloDolphinPlugin::injectFileVersionIntoGeneralTab,
                    Qt::ConnectionType::SingleShotConnection
                );

            }
        }
    }
}

void HelloDolphinPlugin::injectFileVersionIntoGeneralTab(KPageWidgetItem *current, [[maybe_unused]] KPageWidgetItem *before)
{
    string tabName = current->name().toStdString();

    // Remove '&' character used for pneumatics.
    std::regex pattern("&");
    tabName = std::regex_replace(tabName, pattern, "");

    // Looking for General tab to add the File Version
    if (tabName == "General")
    {
        QVBoxLayout *vbox = (QVBoxLayout*) current->widget()->children().first();
        QGridLayout *gridLayout = (QGridLayout*) vbox->children().first();

        QLabel *fileVersionLabelKey = new QLabel(QString::fromUtf8("Version:"));
        QLabel *fileVersionLabelValue = new QLabel(QString::fromUtf8(this->version));

        gridLayout->addWidget(fileVersionLabelKey, 18, 0, Qt::AlignRight|Qt::AlignVCenter);
        gridLayout->addWidget(fileVersionLabelValue, 18, 1, Qt::AlignLeft|Qt::AlignVCenter);
    }
}

bool HelloDolphinPlugin::is_target_file_type(QString fileName)
{
    for (std::string ext: this->ALLOW_LIST)
    {
        if (fileName.endsWith(QString::fromUtf8(ext))) return 1;
    }

    return 0;
}



K_PLUGIN_CLASS_WITH_JSON(HelloDolphinPlugin, "hello-dolphin-plugin.json")


// MOC file
#include "hello-dolphin-plugin.moc"

