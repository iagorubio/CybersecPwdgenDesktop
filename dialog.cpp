/**
 * MIT License
 *
 * Copyright (c) 2021 Yago Rubio Sanfiz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "dialog.h"
#include "ui_dialog.h"
#include <QtMath>
#include <QRandomGenerator>
#include <QList>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::Shuffle(QString str){
    QString result;
    while( true ){
        quint32 v = QRandomGenerator::global()->bounded(str.length());
        result.append(str.at(v));
        str.remove(v,1);
        if( str.length() == 0 ) break;
    }
    return result;
}
QString Dialog::GetRandomString(bool chars, bool capitals, bool sym, int length, int symbols)
{
   const QString numbers("012345678901234567890123456789012345678901234567890123456789");
   const QString lowercase("abcdefghjklmnpqrstuvwxyzabcdefghjklmnpqrstuvwxyzabcdefghjklmnpqrstuvwxyz");
   const QString uppercase("ABCDEFGHJKLMNPQRSTUVWXYZABCDEFGHJKLMNPQRSTUVWXYZABCDEFGHJKLMNPQRSTUVWXYZ");
   const QString symbolsOwasp("!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"); // https://owasp.org/www-community/password-special-characters, minus whitespace
   const QString symbols_AsOi("@%+\\/'!$^?:.(){}[]~`-_.@%+\\/'!$^?:.(){}[]~`-_.@%+\\/'!$^?:.(){}[]~`-_."); //AD and Oracle Identity safe

   QList<QString>  list;

   length = (length + 1) * 8;

   list.append(this->Shuffle(numbers));

   if( chars ){
       list.append(this->Shuffle(lowercase));
   }
   if( capitals ){
       list.append(this->Shuffle(uppercase));
   }
   if( sym ){
        if( symbols == 0 )
            list.append(this->Shuffle(symbolsOwasp));
        else
            list.append(this->Shuffle(symbols_AsOi));
   }

   QString randomString;

   int c = 0;
   while( c < length ){
       for(int i=0; i<list.length(); ++i)
       {
           QString current = list.at(i);
           int index = QRandomGenerator::global()->generate() % current.length();
           QChar nextChar = current.at(index);
           randomString.append(nextChar);

           if( ++c >= length ) break;
       }
   }
   return randomString;
}

void Dialog::on_pushButton_createPwd_clicked()
{
    bool bLowercase = ui->checkBox_Lowercase->isChecked();
    bool bUppercase = ui->checkBox_Upercase->isChecked();
    bool bSymbols = ui->checkBox_symbols->isChecked();
    int sizeIndex = ui->comboBox_size->currentIndex();
    int symbolIndex = ui->comboBox_symbols->currentIndex();

    ui->passwordOutputText->setText(GetRandomString(bLowercase, bUppercase, bSymbols, sizeIndex, symbolIndex));
}


void Dialog::on_pushButton_Close_clicked()
{
    close();
}

