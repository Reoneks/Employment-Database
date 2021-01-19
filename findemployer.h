#ifndef FINDEMPLOYER_H
#define FINDEMPLOYER_H
#include <QWidget>
namespace Ui {
class FindEmployer;
}
class FindEmployer : public QWidget{
    Q_OBJECT
    QString Company,Requirements,Description,Vacancy,Salary,ID;
    public:
        explicit FindEmployer(QWidget *parent = nullptr);
        void SetData(QString Company,QString Requirements,QString Description,QString Vacancy,QString Salary);
        void SetInternalData();
        QVector<QString> GetData(QString Account);
        QVector<QString> GetData();
        QString GetID();
        void SetID(QString ID);
        void Employer();
        void AllowEdit();
        QString GetVacancyName();
        FindEmployer& operator = (const FindEmployer& right){
            if(this==&right){
                return *this;
            }
            Company=right.Company;
            Requirements=right.Requirements;
            Description=right.Description;
            Vacancy=right.Vacancy;
            Salary=right.Salary;
            ID=right.ID;
            return *this;
        }
        ~FindEmployer();
    signals:
        void OpenInfo();
    private slots:
        void on_pushButton_clicked();

private:
        Ui::FindEmployer *ui;
};
#endif // FINDEMPLOYER_H
