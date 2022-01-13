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
#include "cpasswordgenerator.h"

CPasswordGenerator::CPasswordGenerator(){}

/**
 * @brief CPasswordGenerator::GetRandomString Creates a pseudo-random string.
 *      This class creates a pseudo-random string by joining and shuffling character vectors selected
 *      by the user. The lower and upper characters sets does not include the characters I and O so they
 *      are not mistaked for the numbers one and zero.
 * @param chars wether to include lower case characters
 * @param capitals wether to include upper case characters
 * @param sym wether to include symbols
 * @param length integer with the password length
 * @param symbols SYMBOLS_OWASP use owasp symbols SYMBOLS_AD_OI use Active Directory/Oracle Identity safe symbols
 * @return QString with the password
 */
QString CPasswordGenerator::GetRandomString(bool chars, bool capitals, bool sym, int length, int symbols)
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
        if( symbols == SYMBOLS_OWASP )
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

/**
 * @brief CPasswordGenerator::Shuffle shuffles a string
 *      Shuffles a string by taking a random character out of the string to
 *      a new character string. Not the best algorithm but it's just for ~20 character's
 *      sets so the gain of optimicing this function won't be
 * @param str with the characters to suffle
 * @return string the shuffled characters
 */
QString CPasswordGenerator::Shuffle(QString str){
    QString result;
    while( true ){
        quint32 v = QRandomGenerator::global()->bounded(str.length());
        result.append(str.at(v));
        str.remove(v,1);
        if( str.length() == 0 ) break;
    }
    return result;
}
