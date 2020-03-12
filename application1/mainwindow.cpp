#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include <QDataStream>
#include <QDateTime>
#include <QTime>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <QFileDialog>
#include <QValidator>
#include <QRegExpValidator>
#include <stddef.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <streambuf>



const quint32 Crc32Table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
    0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
    0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
    0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
    0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
    0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
    0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
    0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
    0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
    0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
    0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
    0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
    0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
    0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
    0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
    0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
    0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
    0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
    0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
    0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
    0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
    0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
    0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
    0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
    0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
    0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
    0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

void Crc32b(quint32 *crc, unsigned char buf)
{
  *crc = (*crc >> 8) ^ Crc32Table[(*crc ^ buf) & 0xFF];
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QRegExp rx("0x\[\\d A-F]{1,2}");

    ui->lineEdit_3->setValidator(new QIntValidator (100000, 10000000));
    ui->lineEdit_2->setValidator(new QRegExpValidator(rx, this));

    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(createFile()));
    connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(contrSum()));

}
void MainWindow::createFile()
{

    QString fileName = QFileDialog::getSaveFileName
        (this, tr("file"), tr("name"), "Бинарный файл (*.bin)");
    if (true == fileName.isEmpty()) {
       return;
    }

    QDateTime start = QDateTime::currentDateTime();
    ui->textBrowser->append("Начало создания файла: "+start.toString("hh:mm:ss"));

    FILE *fp;

    QString str = ui->lineEdit->text();

    if((fp = fopen(fileName.toLocal8Bit().data(), "wb"))== NULL){
        qDebug() << "Cannot open file.";
        exit (1);
    }

    char ba[1024];

    if (ui->radioButton->isChecked()) {
        for (int j = 0; j < 1024; j++) {

            ba[j] = 0;
        }
        quint64 size = str.toLongLong();
        int BlockSize;
        do
        {
          BlockSize = 1024;
          if (size < 1024) BlockSize = size;
          fwrite(ba, 1, BlockSize, fp);
          size -= BlockSize;
        } while (size);
    }
    if (ui->radioButton_2->isChecked()) {
        for (int j = 0; j < 1024; j++) {

            ba[j] = 0xFF;
        }
        quint64 size = str.toLongLong();
        int BlockSize;
        do
        {
          BlockSize = 1024;
          if (size < 1024) BlockSize = size;
          fwrite(ba, 1, BlockSize, fp);
          size -= BlockSize;
        } while (size);
    }
    if (ui->radioButton_4->isChecked()) // Случайные значения
    {
      qsrand(time(0));
      quint64 FSize = str.toLongLong();
      int BlockSize;
      do
      {
        BlockSize = 1024;
        if (FSize < 1024) BlockSize = FSize;
        for (int j = 0; j < BlockSize; j++)
          ba[j] = qrand() % 256;
        fwrite(ba, 1, BlockSize, fp);
        FSize -= BlockSize;
      } while (FSize);
    }
    if (ui->radioButton_3->isChecked()) {
        QString sstr = ui->lineEdit_2->text();

        for (int j = 0; j < 1024; j++) {

            ba[j] = sstr.toInt(0,16);

        }
        quint64 size = str.toLongLong();
        int BlockSize;
        do
        {
          BlockSize = 1024;
          if (size < 1024) BlockSize = size;
          fwrite(ba, 1, BlockSize, fp);
          size -= BlockSize;
        } while (size);
    }

    if (ui->radioButton_5->isChecked()) {
        unsigned char ba1[256];

        for (int j = 0; j < 256; j++) {
            ba1[j] = j;

        }

        quint64 size1 = str.toLongLong();
        int BlockSize1;

        do
        {
          BlockSize1 = 256;
          if (size1 < 256) BlockSize1 = size1;
          fwrite(ba1, 1, BlockSize1, fp);
          size1 -= BlockSize1;
        } while (size1);

    }

    if (ui->radioButton_6->isChecked()) // 32-разрядный счётчик
    {
      quint64 FSize = str.toLongLong();
      if (FSize % 4)
      {
        ui->textBrowser->append("Ошибка! В режиме 32-х разрядного счётчика длина файла должна быть кратна четырём");
        fclose(fp);
        return;
      }
      char Buf[256];
      unsigned int Count = 0;
      do
      {
        int BlockSize = 256;
        if (FSize < 256) BlockSize = FSize;
        for (int j = 0; j < 64; j++) ((unsigned int*)Buf)[j] = Count++;qDebug()<< Count;
        fwrite(Buf, 1, BlockSize, fp);
        FSize -= BlockSize;
      } while (FSize);
    }

    fclose(fp);

    QDateTime finish = QDateTime::currentDateTime();

    ui->textBrowser->append("Файл создан: "+finish.toString("hh:mm:ss"));

}


void MainWindow::contrSum()
{
    QString filename1 = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),QDir::currentPath(),"Бинарный файл (*.bin);;Все файлы (*.*)");

//    QString FileName =
//        QFileDialog::
//          getOpenFileName(0, "Загрузка параметров эквалайзера", "",
//                          "Файлы характеристик (*.fch);;Все файлы (*.*)");

    if (true == filename1.isEmpty()) {
       return;
    }

    QString str4 = ui->lineEdit_3->text();

    int BlockSize2 = str4.toInt();

    if( str4==NULL || BlockSize2 < 100000 || BlockSize2 > 10000000) {

      ui->textBrowser->append("Неверный размер блока.");
      return;
    }
    QDateTime start1 = QDateTime::currentDateTime();
    ui->textBrowser->append("Начало подсчёта контрольных сумм: "+start1.toString("hh:mm:ss"));
    qint64 size2 = filesize(filename1.toStdString().c_str());

    unsigned char *ba4 = new unsigned char[BlockSize2];


    FILE *fp4;
       if((fp4 = fopen(filename1.toStdString().c_str(), "rb"))== NULL){
            qDebug() << "Cannot open file.";
            exit (1);
        }
    FILE *fp1;
         if((fp1 = fopen("result.txt", "w"))== NULL){
             qDebug() << "Cannot open file.";
             exit (1);
         }

    int m = 0;

    do
    {
      if (size2 < BlockSize2) BlockSize2 = size2;
      fread(ba4, sizeof(unsigned char), BlockSize2, fp4);


      quint32 Sum1 = 0xFFFFFFFF;
      int i = 0;
      while (i < BlockSize2){
        Crc32b(&Sum1, ba4[i]);
      Sum1 ^= 0xFFFFFFFF;
      i += 4;
     }
      quint32 Sum2 = 0xFFFFFFFF;
      int j = 1;
      while (j < BlockSize2){
        Crc32b(&Sum2, ba4[j]);
      Sum2 ^= 0xFFFFFFFF;
      j += 4;
     }
      quint32 Sum3 = 0xFFFFFFFF;
      int k = 2;
      while (k < BlockSize2){
        Crc32b(&Sum3, ba4[k]);
      Sum3 ^= 0xFFFFFFFF;
      k += 4;
     }
      quint32 Sum4 = 0xFFFFFFFF;
      int n = 3;
      while (n < BlockSize2){
        Crc32b(&Sum4, ba4[n]);
      Sum4 ^= 0xFFFFFFFF;
      n += 4;
     }

      m += 1;

      char cNewLine = '\n';
      char pLine = ' ';
      char str[50];
      memset(str, 0, sizeof(str));
      sprintf (str, "%s %d%s", "Block ", m, ":");


      char str1[50];
      memset(str1, 0, sizeof(str1));
      sprintf (str1, "%s %s%x", "1. ", "0x", Sum1);

      char str2[50];
      memset(str2, 0, sizeof(str2));
      sprintf (str2, "%s %s%x", "2. ", "0x", Sum2);

      char str3[50];
      memset(str3, 0, sizeof(str3));
      sprintf (str3, "%s %s%x", "3. ", "0x", Sum3);

      char str4[50];
      memset(str4, 0, sizeof(str4));
      sprintf (str4, "%s %s%x", "4. ", "0x", Sum4);

      fwrite(str, sizeof(str), 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);
      fwrite(str1, sizeof(str1), 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);
      fwrite(str2, sizeof(str2), 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);
      fwrite(str3, sizeof(str3), 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);
      fwrite(str4, sizeof(str4), 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);
      fwrite(&pLine, 1, 1, fp1);
      fwrite(&cNewLine, 1, 1, fp1);

      size2 -= BlockSize2;

    } while (size2);
     delete [] ba4;
     fclose(fp4);
     fclose(fp1);
     QDateTime finish1 = QDateTime::currentDateTime();
     ui->textBrowser->append("Контрольные суммы подсчитаны: "+finish1.toString("hh:mm:ss"));


}


MainWindow::~MainWindow()
{
    delete ui;
}

