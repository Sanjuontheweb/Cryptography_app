#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

class BackendBridge : public QObject {
    Q_OBJECT

public:
    explicit BackendBridge(QObject *parent = nullptr);

signals:
    void resultReady(QString result);

public slots:
    void callC_main(QString file_action);
    void callS_main(QString sign_action);
    void openUsage();
};

#endif // BRIDGE_H
