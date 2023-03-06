#include "CopySymbolPlugin.h"

#include <MainWindow.h>

#include <qapplication.h>
#include <qclipboard.h>

// Adapted from "SamplePlugin" examples from the Cutter repo (GPLv3)

void CopySymbolPlugin::setupPlugin() {}


static void CopySymbolToClipboard(uintptr_t address)
{
    CutterCore* core = Core();
    RVA functionStart = core->getFunctionStart(address);
    // TODO can you get the symbol from this?
    //RzAnalysisFunction* func = core->functionAt(functionStart);
    auto symbols = core->getAllSymbols();
    for (int i = 0; i < symbols.size(); ++i)
    {
        if (symbols[i].vaddr == functionStart)
        {
            //core->message(symbols[i].name);
            QClipboard* clipboard = QApplication::clipboard();
            clipboard->setText(symbols[i].name);
            return;
        }
    }

    // not found - error
    QMessageBox error;
    RzAnalysisFunction* func = core->functionAt(functionStart);
    if (func == nullptr)
    {
        error.setText("Function not found.");
        error.setInformativeText("Target function probably hasn't been analysed.");
    }
    else if (func->name)
        error.setText("Symbol for function " + QString(func->name) + " not found");
    else
        error.setText("Error");

    error.exec();
}

void CopySymbolPlugin::setupInterface(MainWindow *main)
{
    addressableAction = main->getContextMenuExtensions(MainWindow::ContextMenuType::Addressable)->addAction("Copy symbol");
    QMetaObject::Connection con1 = connect(addressableAction, &QAction::triggered, this, [this]() 
    {
        // get address
        uintptr_t address = addressableAction->data().toULongLong();
        CopySymbolToClipboard(address);
    });

    disassemblyAction = main->getContextMenuExtensions(MainWindow::ContextMenuType::Disassembly)->addAction("Copy symbol");
    QMetaObject::Connection con2 = connect(disassemblyAction, &QAction::triggered, this, [this]()
    {
        // get address
        uintptr_t address = disassemblyAction->data().toULongLong();
        CopySymbolToClipboard(address);
    });

    if(!con1 || !con2)
        Core()->message("CopySymbolPlugin: Connection failed");


    Core()->message("CopySymbolPlugin: loaded");
}
