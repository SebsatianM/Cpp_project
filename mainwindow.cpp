#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->groupBox->setStyleSheet("QGroupBox::groupBox {subcontrol-position: top;}");
    mydb =QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/home/sebastian/Pulpit/DB/mydb.project");

    if (!mydb.open())
    {
        ui->db_status_label->setText("Nie połączono z bazą danych");
    }
    else
    {
        ui->db_status_label->setText("Prawidłowo połączono z bazą danych");
    }

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_add_fields_box_clicked()
{

    QString name = ui->f_name_lineEdit->text();
    QString area = ui->area_lineEdit->text();

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Nazwa'");
        }
    else if (area.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Powierzchnia'");
        }
    else if(!mydb.isOpen())
    {
            QMessageBox::information(this, "Błąd", "Problem z bazą danych");
    }
    QSqlQuery query;
    query.prepare("INSERT into fields (name,area) VALUES ('"+name+"','"+area+"')");
    if(query.exec())
   {
       QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowe pole"));
   }else
    {
        QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
    }


}
