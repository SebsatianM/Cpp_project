#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

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
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowy traktor"));
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
   if (index==1)
   {
       loadFieldsToTaskTab();
       loadWorkTypesToTaskTab();

   }else if (index==2)
   {
       loadFieldsToEditList();
       loadTractorsToEditList();
       loadWorkTypesToEditLists();
   }else if (index==3) loadTractorListToComboBox();

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
        query.prepare("INSERT INTO work_types (name,tractor,fuel_cons) SELECT '"+name+"','"+t_name+"','"+f_cons+"' WHERE NOT EXISTS(SELECT 1 FROM work_types WHERE name='"+name+"' AND tractor='"+t_name+"')");
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
    //qDebug()<<name;
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
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potrzebne potwierdzenie!", "Jesteś pewny, że chcesz to usunąć?",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
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
      }else
      {
          QMessageBox::information(this, tr("Anulowano"), tr("Na szczęście nic nie usunięto. Bądź ostrożny!"));
      }

}

void MainWindow::on_f_edit_save_button_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potrzebne potwierdzenie!", "Jesteś pewny, że chcesz to zmienić?",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
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
    }else
      {
          QMessageBox::information(this, tr("Anulowano"), tr("Na szczęście nic nie zmienono. Sprawdź jeszcze raz!"));
      }
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
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potrzebne potwierdzenie!", "Jesteś pewny, że chcesz to usunąć?",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {
        QString name = ui->t_edit_name_lineEdit->text();
        connOpen();
        QSqlQuery query,query2;
            query.prepare("DELETE FROM tractors where name='"+name+"'");
            query2.prepare("DELETE FROM work_types where tractor='"+name+"'");
            if(query.exec() && query2.exec())
            {
                QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo usunięto traktor"));
                loadTractorsToEditList();
            }
            else
            {
                QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
            }
        connClose();
       }else
      {
          QMessageBox::information(this, tr("Anulowano"), tr("Na szczęście nic nie usunięto. Bądź ostrożny!"));
      }

}

void MainWindow::on_t_edit_save_button_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potrzebne potwierdzenie!", "Jesteś pewny, że chcesz to zmienić?",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
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

      }else
      {
           QMessageBox::information(this, tr("Anulowano"), tr("Na szczęście nic nie zmienono. Sprawdź jeszcze raz!"));
      }


}

void MainWindow::on_wt_name_list_currentIndexChanged(const QString &name)
{
        connOpen();

        QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(mydb);

        query->prepare("SELECT tractor FROM work_types where name='"+name+"'");
        query->exec();
        modal->setQuery(*query);
        ui->wt_edit_t_list->setModel(modal);
        connClose();
}

void MainWindow::on_wt_edit_t_list_currentIndexChanged(const QString &t_name)
{
    QString name;
    name = ui->wt_name_list->currentText();
    qDebug()<<t_name;
    qDebug()<<name;
    connOpen();
    QSqlQuery query;

        query.prepare("SELECT fuel_cons FROM work_types WHERE name='"+name+"' AND tractor='"+t_name+"'");
        if(query.exec())
        {
            while(query.next())
            {
                 ui->wt_edit_fcon_lineEdit->setText(query.value(0).toString());
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), query.lastError().text());
        }
    connClose();

}

void MainWindow::on_add_task_button_clicked()
{
    bool isDone = true;
    QDate DateNow,DateSelected;
    QString f_name,wt_name,t_name,desc,done;
    DateSelected = ui->kalendarz->selectedDate();
    if (DateSelected>=DateNow.currentDate())
    {
        isDone = false;
    }
    f_name = ui->f_name_Task_list->currentText();
    wt_name = ui->wt_name_Task_list->currentText();
    t_name = ui->t_name_Task_list->currentText();
    desc = ui->desc_text->toPlainText();

    qDebug()<<isDone;
    qDebug()<<DateSelected.toString("dd-MM-yy");
    qDebug()<<f_name;
    qDebug()<<wt_name;
    qDebug()<<t_name;
    qDebug()<<desc;
    float fuel_use,field_area,used_fuel;
    connOpen();
    QSqlQuery Fuel_query,Area_query,insert_query;

        Fuel_query.prepare("SELECT fuel_cons FROM work_types WHERE name='"+wt_name+"' AND tractor='"+t_name+"'");
        if(Fuel_query.exec())
        {
            while(Fuel_query.next())
            {
                fuel_use = Fuel_query.value(0).toString().toFloat();
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), Fuel_query.lastError().text());
        }

        Area_query.prepare("SELECT area FROM fields WHERE name='"+f_name+"'");
        if(Area_query.exec())
        {
            while(Area_query.next())
            {
                field_area = Area_query.value(0).toString().toFloat();
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), Area_query.lastError().text());
        }

        used_fuel = fuel_use*field_area;

        insert_query.prepare("INSERT INTO tasks ("
                             "f_name,"
                             "type,"
                             "state,"
                             "date,"
                             "description,"
                             "fuel_use)"
                             "VALUES (?,?,?,?,?,?);");
        insert_query.addBindValue(f_name);
        insert_query.addBindValue(wt_name);
        insert_query.addBindValue(isDone);
        insert_query.addBindValue(DateSelected.toString("dd-MM-yyyy"));
        insert_query.addBindValue(desc);
        insert_query.addBindValue(used_fuel);

        if(insert_query.exec())
        {
            QMessageBox::information(this, tr("Sukces"), tr("Prawidłowo dodano nowy prace do historii"));
        }
        else
        {
            QMessageBox::critical(this, tr("Błąd"), insert_query.lastError().text());
        }

    connClose();



}

void MainWindow::on_wt_name_Task_list_currentIndexChanged(const QString &name)
{
    connOpen();

    QSqlQueryModel *modal=new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(mydb);

    query->prepare("SELECT tractor FROM work_types where name='"+name+"'");
    query->exec();
    modal->setQuery(*query);
    ui->t_name_Task_list->setModel(modal);
    connClose();
}
