#ifndef ADMINEDITVACANCY_H
#define ADMINEDITVACANCY_H
#include <QMainWindow>
#include "findemployer.h"
namespace Ui {
class AdminEditVacancy;
}
class AdminEditVacancy : public QMainWindow{
    Q_OBJECT
    QVector<FindEmployer*> Vacancy;
    public:
        explicit AdminEditVacancy(QWidget *parent = nullptr);
        ~AdminEditVacancy();
    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_PrevPage_clicked();
        void on_NextPage_clicked();
    private:
        Ui::AdminEditVacancy *ui;
};
#endif // ADMINEDITVACANCY_H
