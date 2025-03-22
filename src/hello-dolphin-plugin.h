#pragma once

#include <QObject>
#include <QString>

#include <KFileItem>
#include <KPropertiesDialogPlugin>
#include "pe-parser-wrapper.h"

using namespace std;

class HelloDolphinPlugin : public KPropertiesDialogPlugin
{
    Q_OBJECT

public:
    HelloDolphinPlugin(QObject *parent);

protected:
    PEParserWrapper *peWrapper;
    std::string version = "";
    const std::vector<std::string> ALLOW_LIST = {".exe", ".dll"};

    void init();
    void setFileItem(std::string filePath);
    void injectFileVersionIntoGeneralTab(KPageWidgetItem *current, KPageWidgetItem *before);

    bool is_target_file_type(QString fileName);

};
