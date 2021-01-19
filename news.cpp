#include "news.h"
#include "ui_news.h"

News::News(QWidget *parent):QWidget(parent),ui(new Ui::News){
    ui->setupUi(this);
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Новини");
    ui->Topic->setReadOnly(true);
    ui->Heading->setReadOnly(true);
    ui->MainText->setReadOnly(true);
    ui->Topic->setTabChangesFocus(true);
    ui->Heading->setTabChangesFocus(true);
    ui->MainText->setTabChangesFocus(true);
    ID="";
}
void News::SetImage(QByteArray array){
    QPixmap image;
    image.loadFromData(array);
    Image=image.scaled(121,121,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->Image->setPixmap(Image);
}
void News::SetImage(QPixmap image){
    Image=image.scaled(121,121,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->Image->setPixmap(Image);
}
void News::SetData(QString Heading,QString ID,QString Topic,QString MainText){
    this->Heading=Heading;
    this->ID=ID;
    ui->Heading->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">"
                          "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                          "p, li { white-space: pre-wrap; }"
                          "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt;\">"+Heading+"</span></p></body></html>");
    this->Topic=Topic;
    ui->Topic->setText(Topic);
    this->MainText=MainText;
    ui->MainText->setText(MainText);
}
void News::SetInternalData(){
    ui->MainText->setText(MainText);
    ui->Topic->setText(Topic);
    ui->Heading->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd\">"
                          "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                          "p, li { white-space: pre-wrap; }"
                          "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
                          "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt;\">"+Heading+"</span></p></body></html>");
    ui->Image->setPixmap(Image);
}
QVector<QString> News::GetData(){
    QVector<QString> Result;
    Result<<ID<<ui->MainText->toPlainText()<<ui->Topic->toPlainText()<<ui->Heading->toPlainText();
    return Result;
}
void News::AllowEdit(){
    ui->Topic->setReadOnly(false);
    ui->Heading->setReadOnly(false);
    ui->MainText->setReadOnly(false);
}
QByteArray News::GetImage(){
    QPixmap map1=*ui->Image->pixmap();
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    map1.save(&buffer,"PNG");
    return bArray;
}
News::~News(){
    delete ui;
}
