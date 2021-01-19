#ifndef NEWS_H
#define NEWS_H
#include <QWidget>
#include <QBuffer>
namespace Ui {
class News;
}
class News : public QWidget{
    Q_OBJECT
    QString Heading,Topic,MainText,ID;
    QPixmap Image;
    public:
        explicit News(QWidget *parent = nullptr);
        void SetImage(QByteArray array);
        void SetImage(QPixmap image);
        void SetData(QString Heading,QString ID,QString Topic,QString MainText);
        void SetInternalData();
        void AllowEdit();
        QVector<QString> GetData();
        QByteArray GetImage();
        News& operator = (const News& right){
            if(this==&right){
                return *this;
            }
            Heading=right.Heading;
            Topic=right.Topic;
            MainText=right.MainText;
            Image=right.Image;
            ID=right.ID;
            return *this;
        }
        ~News();
    private:
        Ui::News *ui;
};
#endif // NEWS_H
