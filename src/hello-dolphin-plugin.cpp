#include <QWidget>
#include <QObject>
#include <QString>
#include <KPluginFactory>
#include <KActionCollection>

#include <kpluginfactory.h>

#include <KFileWidget>
#include <KFileItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileInfo>


class HelloDolphinPlugin : public KFileWidget
{
    Q_OBJECT

public:

    explicit HelloDolphinPlugin(const QUrl &startDir, QWidget *parent = nullptr)
    : KFileWidget(startDir, parent)
    {
        // Initialize layout and widget for displaying EXE-specific information
        auto *layout = new QVBoxLayout(this);

        // Example label for .exe file info
        m_exeInfoLabel = new QLabel(QString::fromUtf8("No EXE file selected"), this);
        layout->addWidget(m_exeInfoLabel);

        setLayout(layout);
    }

    void setFileItem(const KFileItem &fileItem)
    {
        // Call the base class method to ensure standard file item handling
        // KFileWidget::setFileItem(fileItem);

        // Check if it's an EXE file
        if (fileItem.url().toString().endsWith(QString::fromUtf8(".exe"))) {
            // Update the label with EXE-specific info (e.g., file version)
            QFileInfo fileInfo(fileItem.url().toLocalFile());
            m_exeInfoLabel->setText(QString::fromUtf8("This is an EXE file: %1")
            .arg(fileInfo.fileName()));

            // You can add more custom data related to .exe files here
            // For example, version information, icon, etc.
        } else {
            m_exeInfoLabel->setText(QString::fromUtf8("Selected file is not an EXE file."));
        }
    }

private:
    QLabel *m_exeInfoLabel; // Label to display custom EXE info
};



/*K_PLUGIN_CLASS_WITH_JSON(
    HelloDolphinPlugin, "metadata.json"

)*/

// K_PLUGIN_CLASS(HelloDolphinPlugin)


// MOC file
#include "hello-dolphin-plugin.moc"

