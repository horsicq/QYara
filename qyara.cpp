// Copyright (c) 2019 hors<horsicq@gmail.com>
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
#include "qyara.h"

QYara::QYara(QObject *parent) : QObject(parent)
{
    yr_initialize();
    bRulesLoaded=false;
    yrCompiler=0;
    // TODO: set callback
}

QYara::~QYara()
{
    yr_finalize();
}

bool QYara::loadRulesFile(QString sFileName)
{
    bool bResult=false;

    QFile file;
    file.setFileName(sFileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray baData=file.readAll();

        bResult=loadRules(baData.data());

        file.close();
    }

    return bResult;
}

bool QYara::loadRules(QString sRules)
{
    bool bResult=false;

    freeRules();

    if(yr_compiler_create(&yrCompiler)==ERROR_SUCCESS)
    {
        if(yr_compiler_add_string(yrCompiler,sRules.toLatin1().data(),"Rules")==0)
        {
            bRulesLoaded=true;
            bResult=true;
        }
    }

    return bResult;
}

bool QYara::freeRules()
{
    bool bResult=false;

    if(bRulesLoaded)
    {
        yr_compiler_destroy(yrCompiler);

        bRulesLoaded=false;
        yrCompiler=0;

        bResult=true;
    }

    return bResult;
}

QList<QString> QYara::scanFile(QString sFileName)
{
    listResult.clear();

    if(bRulesLoaded)
    {
        YR_RULES *yrRules=0;

        if(yr_compiler_get_rules(yrCompiler,&yrRules)==ERROR_SUCCESS)
        {
            if(yr_rules_scan_file(yrRules,sFileName.toLatin1().data(),0,(YR_CALLBACK_FUNC)callback_function,(void *)this,0)==ERROR_SUCCESS)
            {
                // TODO
            }

            yr_rules_destroy(yrRules);
        }

    }

    return listResult;
}

int QYara::callback_function(int message,void *message_data,void *user_data)
{
    if(message==CALLBACK_MSG_RULE_MATCHING)
    {
        QString sRecord=QString("%1_%2").arg(((YR_RULE *)message_data)->tags).arg(((YR_RULE *)message_data)->identifier);
        ((QYara *)user_data)->listResult.append(sRecord);
    }

    return CALLBACK_CONTINUE;
}

QYara::RESULT QYara::scanFile(QString sFileName, QString sRules)
{
    RESULT result= {0};
    QElapsedTimer scanTimer;
    scanTimer.start();

    QYara yara;
    yara.loadRules(sRules);
    result.listRecords=yara.scanFile(sFileName);
    result.sFileName=sFileName;
    result.nScanTime=scanTimer.elapsed();

    return result;
}

QString QYara::toText(QYara::RESULT *pResult)
{
    QString sResult;

    int nCount=pResult->listRecords.count();

    for(int i=0; i<nCount; i++)
    {
        sResult+=QString("%1\r\n").arg(pResult->listRecords.at(i));
    }

    return sResult;
}

