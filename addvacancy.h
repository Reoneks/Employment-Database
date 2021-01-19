#ifndef ADDVACANCY_H
#define ADDVACANCY_H
#include <QMainWindow>
namespace Ui {
class AddVacancy;
}
class AddVacancy : public QMainWindow{
    Q_OBJECT
    void ErrorMessage(QString Error);
    QString CompanyName;
    public:
        explicit AddVacancy(QWidget *parent = nullptr);
        void SetCompanyName(QString Name);
        void ClearData();
        ~AddVacancy();
    private slots:
        void on_Ok_clicked();
        void on_Cancel_clicked();
    private:
        Ui::AddVacancy *ui;
};
#endif // ADDVACANCY_H
