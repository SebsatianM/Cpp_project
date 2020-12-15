#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    if (!connOpen())
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


void MainWindow::on_add_field_button_clicked()
{
    QString name = ui->f_name_lineEdit->text();
    QString area = ui->f_area_lineEdit->text();

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Nazwa'");
        }
    else if (area.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Powierzchnia'");
        }
    else
    {
        connOpen();
        QSqlQuery query;
        query.prepare("INSERT into fields (name,area) VALUES ('"+name+"','"+area+"')");
        if(query.exec())
       {
           QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowe pole"));
       }
       else
       {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
       }
       connClose();
    }
}

void MainWindow::on_add_tractor_button_clicked()
{
    QString name = ui->t_name_lineEdit->text();
    QString power = ui->t_power_lineEdit->text();

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Nazwa'");
        }
    else if (power.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Powierzchnia'");
        }
    else
    {
    connOpen();
    QSqlQuery query;
        query.prepare("INSERT into tractors (name,power) VALUES ('"+name+"','"+power+"')");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowe pole"));
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

    }
    loadTractorListToComboBox();
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
   if (index==2)
   {
       loadFieldsToEditList();
       loadTractorsToEditList();
   };
   if (index==3) loadTractorListToComboBox();

}


void MainWindow::on_add_wt_button_clicked()
{
    QString t_name = ui->wt_t_name_comboBox->currentText();
    QString name = ui->wt_name_lineEdit->text();
    QString f_cons = ui->wt_fuel_con_lineEdit->text();
    qDebug()<<name<<f_cons<<t_name;

    if(name.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Nazwa'");
        }
    else if (f_cons.isEmpty())
        {
            QMessageBox::information(this, "Błąd", "Nie wypełniono pola 'Zużycie paliwa'");
        }
    else
    {
    connOpen();
    QSqlQuery query;
        query.prepare("INSERT into work_types (name,tractor,fuel_cons) VALUES ('"+name+"','"+t_name+"','"+f_cons+"')");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowy rodzaj wykonywanej pracy"));
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

    }
}



void MainWindow::on_f_name_list_currentIndexChanged(const QString &name)
{
    qDebug()<<name;
    connOpen();
    QSqlQuery query;
        query.prepare("SELECT * FROM fields where name='"+name+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->f_edit_name_lineEdit->setText(query.value(1).toString());
                ui->f_edit_area_lineEdit->setText(query.value(2).toString());
                ui->f_edit_desc_lineEdit->setText(query.value(3).toString());
            }

        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();
}

void MainWindow::on_f_edit_delete_button_clicked()
{
    QString name = ui->f_edit_name_lineEdit->text();
    connOpen();
    QSqlQuery query;
        query.prepare("DELETE FROM fields where name='"+name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo usunięto pole"));
            loadFieldsToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}

void MainWindow::on_f_edit_save_button_clicked()
{
    QString base_name = ui->f_name_list->currentText();
    QString name = ui->f_edit_name_lineEdit->text();
    QString f_area = ui->f_edit_area_lineEdit->text();
    QString desc = ui->f_edit_desc_lineEdit->text();

    connOpen();
    QSqlQuery query;
        query.prepare("UPDATE fields SET name = '"+name+"',area = '"+f_area+"', description = '"+desc+"' where name='"+base_name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo zmieniono"));
            loadFieldsToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}

void MainWindow::on_t_name_list_currentIndexChanged(const QString &name)
{
    qDebug()<<name;
    connOpen();
    QSqlQuery query;
        query.prepare("SELECT * FROM tractors where name='"+name+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->t_edit_name_lineEdit->setText(query.value(1).toString());
                ui->t_edit_power_lineEdit->setText(query.value(2).toString());
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();
}

void MainWindow::on_t_edit_delete_button_clicked()
{
    QString name = ui->t_edit_name_lineEdit->text();
    connOpen();
    QSqlQuery query;
        query.prepare("DELETE FROM tractors where name='"+name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo usunięto traktor"));
            loadTractorsToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}

void MainWindow::on_t_edit_save_button_clicked()
{
    QString base_name = ui->t_name_list->currentText();
    QString name = ui->t_edit_name_lineEdit->text();
    QString power = ui->t_edit_power_lineEdit->text();


    connOpen();
    QSqlQuery query;
        query.prepare("UPDATE tractors SET name = '"+name+"', power = '"+power+"' where name='"+base_name+"'");
        if(query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo zmieniono"));
            loadTractorsToEditList();
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}
