#include "widget.h"
#include "ui_widget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
QString mFilename ="C:/Users/asus/OneDrive/桌面/QTEX/txt/myfile.txt";

void Write (QString Filename, QString str)
{
    QFile mFile (Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug() <<"could not open file for write";
        return;
    }
    QTextStream out(&mFile);
    out<<str; //將內容輸出至txt檔
    out.flush(); //刷新mFile
    mFile.close(); //關閉mFile
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QStringList ColTotle;

    ui->tableWidget->setColumnCount(4); //設定欄位
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels (ColTotle);
    
    // 設定冷色系配色
    // 主視窗背景：淡藍灰色
    this->setStyleSheet("QWidget { background-color: #E8F4F8; }");
    
    // 表格樣式：藍綠色系
    ui->tableWidget->setStyleSheet(
        "QTableWidget {"
        "   background-color: #F0F8FF;"
        "   alternate-background-color: #E1F5FE;"
        "   gridline-color: #81D4FA;"
        "   selection-background-color: #4FC3F7;"
        "   selection-color: white;"
        "   border: 2px solid #4FC3F7;"
        "   border-radius: 5px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #0288D1;"
        "   color: white;"
        "   padding: 5px;"
        "   border: 1px solid #0277BD;"
        "   font-weight: bold;"
        "}"
        "QTableWidget::item {"
        "   padding: 5px;"
        "}"
    );
    ui->tableWidget->setAlternatingRowColors(true);
    
    // 按鈕樣式：藍色調
    QString buttonStyle = 
        "QPushButton {"
        "   background-color: #0288D1;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 5px;"
        "   padding: 10px 20px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0277BD;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #01579B;"
        "}";
    
    ui->pushButton->setStyleSheet(buttonStyle);
    ui->pushButton_2->setStyleSheet(buttonStyle);
    ui->pushButton_3->setStyleSheet(buttonStyle);
    ui->pushButton_4->setStyleSheet(buttonStyle);
    
    // 輸入框樣式：淡藍色邊框
    QString lineEditStyle = 
        "QLineEdit {"
        "   background-color: white;"
        "   border: 2px solid #4FC3F7;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   selection-background-color: #81D4FA;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #0288D1;"
        "}";
    
    ui->lineEdit->setStyleSheet(lineEditStyle);
    ui->lineEdit_2->setStyleSheet(lineEditStyle);
    ui->lineEdit_3->setStyleSheet(lineEditStyle);
    ui->lineEdit_4->setStyleSheet(lineEditStyle);
    
    // 標籤樣式：深藍色文字
    QString labelStyle = 
        "QLabel {"
        "   color: #01579B;"
        "   font-weight: bold;"
        "   font-size: 13px;"
        "}";
    
    ui->label->setStyleSheet(labelStyle);
    ui->label_2->setStyleSheet(labelStyle);
    ui->label_3->setStyleSheet(labelStyle);
    ui->label_4->setStyleSheet(labelStyle);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QTableWidgetItem *col1,*col2,*col3,*col4;

    col1 =new QTableWidgetItem(QString(ui->lineEdit->text()));
    col2 =new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    col3= new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    col4= new QTableWidgetItem(QString(ui->lineEdit_4->text()));
    int rc = ui->tableWidget->rowCount();
    qDebug() << rc << "\n";
    ui->tableWidget->insertRow(rc);
    ui->tableWidget->setItem(rc,0,col1);
    ui->tableWidget->setItem(rc,1,col2);
    ui->tableWidget->setItem(rc,2,col3);
    ui->tableWidget->setItem(rc,3,col4);

}


void Widget::on_pushButton_2_clicked()
{
    QString saveFile="";
    int rc, cc;
    rc=ui->tableWidget->rowCount();
    cc=ui->tableWidget->columnCount();
    for(int i=0; i< rc; i++)
    {
        for(int j=0; j<cc;j++)
            saveFile += ui->tableWidget->item(i,j)->text()+",";
        saveFile+="\n";
    }
    Write(mFilename, saveFile);
}


void Widget::on_pushButton_3_clicked()
{
    // 使用檔案對話框選擇要匯入的txt檔案
    QString fileName = QFileDialog::getOpenFileName(this,
        QStringLiteral("選擇要匯入的檔案"), 
        "",
        QStringLiteral("文字檔案 (*.txt);;所有檔案 (*.*)"));
    
    if (fileName.isEmpty()) {
        return; // 使用者取消選擇
    }
    
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, QStringLiteral("錯誤"), 
            QStringLiteral("無法開啟檔案進行讀取"));
        return;
    }
    
    QTextStream in(&file);
    
    // 清空現有的表格資料
    ui->tableWidget->setRowCount(0);
    
    // 讀取檔案並解析每一行
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        
        // 確保有4個欄位 (學號,班級,姓名,電話)
        if (fields.size() >= 4) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            
            for (int i = 0; i < 4 && i < fields.size(); i++) {
                QTableWidgetItem *item = new QTableWidgetItem(fields[i].trimmed());
                ui->tableWidget->setItem(row, i, item);
            }
        }
    }
    
    file.close();
    QMessageBox::information(this, QStringLiteral("成功"), 
        QStringLiteral("檔案匯入成功！"));
}


void Widget::on_pushButton_4_clicked()
{
    on_pushButton_2_clicked();
    close();
}

