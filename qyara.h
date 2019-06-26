#ifndef QDISASM_H
#define QDISASM_H

#include <QObject>
#include <QFile>
#include "yara.h"
#include <QElapsedTimer>
#undef parent // Conflict with Qt 4.XX

class QYara : public QObject
{
    Q_OBJECT
public:
    struct RESULT
    {
        qint64 nScanTime;
        QString sFileName;
        QList<QString> listRecords;
    };

    explicit QYara(QObject *parent = nullptr);
    ~QYara();
    bool loadRulesFile(QString sFileName);
    bool loadRules(QString sRules);
    bool freeRules();
    QList<QString> scanFile(QString sFileName);
    static int callback_function(int message,void *message_data,void *user_data);

    static RESULT scanFile(QString sFileName,QString sRules);
    static QString toText(RESULT *pResult);
private:

signals:
    void errorMessage(QString sText);
public slots:

protected:
private:
    bool bRulesLoaded;
    YR_COMPILER *yrCompiler;
    QList<QString> listResult;
};

#endif // QDISASM_H
