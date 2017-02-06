/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "csvreader.h"

CsvReader::CsvReader()
{

}

CsvReader::~CsvReader()
{

}

void CsvReader::readCSV(QString fileName, TableModel *model)
{
    if(model == NULL)
    {
        qDebug() << "CsvReader: null model";
        return;
    }

    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        model->clear();
        width = -1;
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        unsigned int counter = 0;
        while (!textStream.atEnd()) {
            if(counter++ % 100000 == 0) {
                qDebug() << "processing: " << counter;
            }
            textStream >> character;
            if (character == ',') {
                checkString(temp, model, character);
            } else if (character == '\n') {
                checkString(temp, model, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp, model);
            } else {
                temp.append(character);
            }
        }
    }
}

void CsvReader::checkString(QString &temp, TableModel* model, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
            temp.remove( QRegExp("^\"") );
            temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
//        temp.replace("\"\"", "\"");
        bool isDouble = false;
        double value = temp.toDouble(&isDouble);
        if(!isDouble)
        {
            temp = "NaN";
        }
        rowValues.append(value);
        if (character != QChar(',')) {
            model->appendRow(rowValues);
            rowValues.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}
