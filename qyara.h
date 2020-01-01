// copyright (c) 2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef QYARA_H
#define QYARA_H

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

    explicit QYara(QObject *parent=nullptr);
    ~QYara();
    bool loadRulesFile(QString sFileName);
    bool loadRules(QString sRules);
    void freeRules();
    RESULT scanFile(QString sFileName);
    static int callback_function(int message,void *message_data,void *user_data);

    static RESULT scanFile(QString sFileName,QString sRules);
    static QString toText(RESULT *pResult);

signals:
    void errorMessage(QString sText);

private:
    bool bCompilerLoaded;
    bool bRulesLoaded;
    YR_COMPILER *yrCompiler;
    YR_RULES *yrRules;
    QList<QString> listResult;
};

#endif // QYARA_H
