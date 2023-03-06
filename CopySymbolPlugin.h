#ifndef CUTTERSYMBOLNAMEPLUGIN_H
#define CUTTERSYMBOLNAMEPLUGIN_H

#include <CutterPlugin.h>

// Adapted from "SamplePlugin" examples from the Cutter repo (GPLv3)

class CopySymbolPlugin : public QObject, CutterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "re.rizin.cutter.plugins.CutterPlugin")
    Q_INTERFACES(CutterPlugin)

public:
    void setupPlugin() override;
    void setupInterface(MainWindow *main) override;

    QString getName() const override { return "Copy Symbol Plugin"; }
    QString getAuthor() const override { return "Bryden Frizzell"; }
    QString getDescription() const override { return "A plugin for copying symbol names."; }
    QString getVersion() const override { return "1.0"; }

private:
    QAction* addressableAction;
    QAction* disassemblyAction;

};

#endif // CUTTERSYMBOLNAMEPLUGIN_H
