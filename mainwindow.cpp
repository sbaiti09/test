#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<employer.h>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QThread>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include "EmailSender.h"
#include<smtp.h>
#include "CalendarWidget.h"

using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Reservation reservation;
    ui->tab_reservation->setModel(reservation.afficher());

    ui->CA_type->addItem("Familiale");
      ui->CA_type->addItem("de Groupe");
      ui->CA_type->addItem("avec Remboursement");
      ui->CA_type->addItem("Non Remboursable");
      ui->CA_type->addItem("Spéciale");
      ui->CA_type->addItem(" à Long Terme");
      ui->CA_type->setCurrentText("choisire un type");
///////// calendrier
          QList<QDate> reservationDates = Reservation::getAllStartDates();

          QTextCharFormat highlightFormat;
          highlightFormat.setBackground(Qt::green);

          for (const QDate &date : reservationDates) {
              ui->calendarWidget1->setDateTextFormat(date, highlightFormat);
          }
/////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;


}


void MainWindow::on_btA_clicked()
{
    QString nom=ui->LA_Nom->text();
     QString type=ui->CA_type->currentText();
     QDate datdebut=ui->DA_D->date();
     QDate datfin=ui->DA_F->date();

        QMessageBox::StandardButton Confirmation;
        Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment ajouter cette réservation?",
                                        QMessageBox::Yes | QMessageBox::No);
        if (Confirmation == QMessageBox::Yes) {
            Reservation r(nom, datdebut, datfin, type);
            bool test = r.ajouter();

        if(test){
              Reservation reservation;
              ui->tab_reservation->setModel(reservation.afficher());
            QMessageBox::information (nullptr, QObject::tr("OK"),
                                       QObject::tr("Ajout effectué \n"
                                      "Click Cancel to exit."), QMessageBox::Ok);
        }
        else
            QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                       QObject::tr("Ajout non effectué \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
}




void MainWindow::on_BTM_clicked()
{
    int id=ui->LM_ID->text().toInt();
    QString nom=ui->LM_nom->text();
     QString type=ui->CM_type->currentText();
     QDate datdebut=ui->DM_D->date();
     QDate datfin=ui->DM_F->date();
     QMessageBox::StandardButton Confirmation;
     Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier cette réservation?" ,
                                     QMessageBox::Yes | QMessageBox::No);
     if (Confirmation == QMessageBox::Yes) {
     Reservation r(nom,datdebut,datfin,type);

        bool test=r.modifier(id);

        if(test){
            Reservation reservation;
            ui->tab_reservation->setModel(reservation.afficher());
            QMessageBox::information (nullptr, QObject::tr("OK"),
                                       QObject::tr("Modification effectué \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                       QObject::tr("Modification non effectué \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
     }
}

void MainWindow::on_BTRCH_clicked()
{
    int id=ui->LM_ID->text().toInt();
    if(id!=NULL){
        Reservation r;
        r.recherche(id);
        if(r.getNom()==NULL){
            QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                       QObject::tr("Valier saisir une id valid \n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else{

            ui->CM_type->addItem("Familiale");
              ui->CM_type->addItem("de Groupe");
              ui->CM_type->addItem("avec Remboursement");
              ui->CM_type->addItem("Non Remboursable");
              ui->CM_type->addItem("Spéciale");
              ui->CM_type->addItem(" à Long Terme");
           ui->LM_nom->setText(r.getNom());
           ui->CM_type->setCurrentText(r.getType());
           ui->DM_D->setDate(r.getDateDebut());
           ui->DM_F->setDate(r.getDateFin());

        }
    }
}

void MainWindow::on_BTSUP_clicked()
{
    Reservation reservation;
    int id = ui->LS_Id->text().toInt();
    QMessageBox::StandardButton Confirmation;
    Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment modifier cette réservation?" ,
                                    QMessageBox::Yes | QMessageBox::No);
    if (Confirmation == QMessageBox::Yes) {
    bool test = reservation.supprimer(id);
    if (test) {
        ui->tab_reservation->setModel(reservation.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée"), QMessageBox::Cancel);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée"), QMessageBox::Cancel);
    }
    }
}

void MainWindow::on_RBdtdebut_toggled(bool checked)
{
    if(checked){this->etattrie="dateDebut";
    ui->TBtrie->setText("Affichage trier selon date Debut par ordre");}
}

void MainWindow::on_RBdf_toggled(bool checked)
{
    if(checked){this->etattrie="dateFin";
    ui->TBtrie->setText("Affichage trier selon date Fin par ordre");}
}

void MainWindow::on_RBnom_toggled(bool checked)
{
    if(checked){this->etattrie="nom";
    ui->TBtrie->setText("Affichage trier selon nom par ordre");
}
}
void MainWindow::on_RBC_clicked()
{
    if(this->etattrie==""){
       QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Valier choisir une option pour trier \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
   }
    else {
        Reservation Reservation;
        ui->tab_reservation->setModel(Reservation.trier(this->etattrie,true));
    }
}

void MainWindow::on_RBdc_clicked()
{
    if(this->etattrie==""){
       QMessageBox::information (nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Valier choisir une option pour trier \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
   }
    else {
        Reservation Reservation;
        ui->tab_reservation->setModel(Reservation.trier(this->etattrie,false));
    }
}

void MainWindow::on_BTRCH_7_clicked()
{
    Reservation reservation;
        QMap<QString, int> stats = reservation.statistiquesParType();

        QPieSeries *series = new QPieSeries();
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            series->append(it.key(), it.value());
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Réservations par Type");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(480, 240);

        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addWidget(chartView);
        ui->layoutGraph->setScene(scene);
}

void MainWindow::on_BTRCH_8_clicked()
{
    qDebug() <<"ccccccccccccccccccccccc";
    EmailSender *emailSender = new EmailSender("issmailchouikhi6@gmail.com", "issmailchouikhi6@gmail.com", "Subject here", "Body here");
        emailSender->sendMail();
}

void MainWindow::on_BTRCH_9_clicked()
{
    CalendarWidget *calendarWidget = new CalendarWidget(this);

        // Récupérer toutes les dates de début des réservations
        QList<QDate> reservationDates = Reservation::getAllStartDates();

        // Marquer les dates de début des réservations sur le calendrier
         calendarWidget->markReservationDates(reservationDates);

        // Ajouter le calendrier à la fenêtre principale
        setCentralWidget(calendarWidget);
}
