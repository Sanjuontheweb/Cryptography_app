// qt_gui/backend_bridge.cpp
#include "bridge.h"
#include "../backend/cryption/cryption_main.hpp"
#include "../backend/cypher/verify_main.hpp"

#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

BackendBridge::BackendBridge(QObject *parent) : QObject(parent) {}

void BackendBridge::callC_main(QString file_action) {
    QString res = c_main(file_action);
    emit resultReady(res);
}

void BackendBridge::callS_main(QString sign_action) {
    QString res2 = s_main(sign_action);
    emit resultReady(res2);
}

void BackendBridge::openUsage() {
    // Get a safe path to the Temp folder
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/usage.txt";
    QString resourcePath = ":/qt/qml/gui_for_cypher/usage.txt";

    if (!QFile::exists(resourcePath)) {
        qDebug() << "Cannot find usage guide at" << resourcePath;
        return;
    }

    // If an old temp file exists, remove it first
    if (QFile::exists(tempPath)) {
        QFile::remove(tempPath);
    }

    // Try to copy the file out of the EXE to the Temp folder
    if (QFile::copy(resourcePath, tempPath)) {
        // Set permissions so Windows can read it
        QFile::setPermissions(tempPath, QFileDevice::ReadUser | QFileDevice::WriteUser);

        // Open it using the correct URL format
        bool ok = QDesktopServices::openUrl(QUrl::fromLocalFile(tempPath));
        if (!ok) qDebug() << "Some error with permissions, so Windows can't open the file.";
    }
    else {
        qDebug() << "Couldn't make a duplicate of the guide";
    }
}
