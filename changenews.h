#ifndef CHANGENEWS_H
#define CHANGENEWS_H
#include <QMainWindow>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include "news.h"
namespace Ui{
class ChangeNews;
}
class ChangeNews:public QMainWindow{
    Q_OBJECT
    QVector<News*> NewsWidget,NewNews;
    int position;
    QGridLayout *hlayout;
    QLabel *label;
    QPushButton *Yes,*No;
    QWidget *mainWindow1;
    public:
        explicit ChangeNews(QWidget *parent = nullptr);
        void SetNews(QVector<News*> NewsWidget);
        ~ChangeNews();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_ChangeImage_clicked();
        void on_NewNews_clicked();
        void on_horizontalSlider_valueChanged(int value);
        void on_DeleteNews_clicked();
        void StartDelete();
        void BreakDelete();
    private:
        Ui::ChangeNews *ui;
};
#endif // CHANGENEWS_H
