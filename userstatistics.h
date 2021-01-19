#ifndef USERSTATISTICS_H
#define USERSTATISTICS_H
#include <QMainWindow>
#include <QChart>
#include <QBarSeries>
#include <math.h>
#include <QBarSet>
#include <QBarCategoryAxis>
namespace Ui {
class UserStatistics;
}
using namespace QtCharts;
class UserStatistics : public QMainWindow{
    Q_OBJECT
    QBarSet *set0,*set1;
    QBarSeries *series;
    QChart *chart;
    QBarCategoryAxis *axis;
    public:
        explicit UserStatistics(QWidget *parent = nullptr);
        void LoadData(QVector<QVector<QString>>Result,QVector<QVector<QString>>Result1);
        ~UserStatistics();
    private:
        Ui::UserStatistics *ui;
};
#endif // USERSTATISTICS_H
