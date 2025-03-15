#pragma once

#include <QObject>
#include <KFileItem>
#include <KPropertiesDialogPlugin>

class HelloDolphinPlugin : public KPropertiesDialogPlugin
{
    Q_OBJECT

public:
    HelloDolphinPlugin(QObject *parent);
    void setFileItem(const KFileItem &fileItem);
    void init();

};
