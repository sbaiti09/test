#include "employer.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

Employer::Employer() {}

Employer::Employer(QString nom, QString prenom, QDate dateNaissance, double salaire, int motDePasse, QString departement, QString poste, int cin)
    : nom(nom), prenom(prenom), dateNaissance(dateNaissance), salaire(salaire), motDePasse(motDePasse), departement(departement), poste(poste), cin(cin) {}

bool Employer::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYER (NOM, PRENOM, DATE_NAISSANCE, SALAIRE, MOT_DE_PASSE, DEPARTEMENT, POSTE, CIN) "
                  "VALUES (:NOM, :PRENOM, :DATE_NAISSANCE, :SALAIRE, :MOT_DE_PASSE, :DEPARTEMENT, :POSTE, :CIN)");
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", dateNaissance);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":MOT_DE_PASSE", motDePasse);
    query.bindValue(":DEPARTEMENT", departement);
    query.bindValue(":POSTE", poste);
    query.bindValue(":CIN", cin);
    return query.exec();
}

bool Employer::modifier(int cin) {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYER SET NOM = :NOM, PRENOM = :PRENOM, DATE_NAISSANCE = :DATE_NAISSANCE, SALAIRE = :SALAIRE, "
                  "MOT_DE_PASSE = :MOT_DE_PASSE, DEPARTEMENT = :DEPARTEMENT, POSTE = :POSTE WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":DATE_NAISSANCE", dateNaissance);
    query.bindValue(":SALAIRE", salaire);
    query.bindValue(":MOT_DE_PASSE", motDePasse);
    query.bindValue(":DEPARTEMENT", departement);
    query.bindValue(":POSTE", poste);
    return query.exec();
}

bool Employer::supprimer(int cin) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYER WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);
    return query.exec();
}

QSqlQueryModel* Employer::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYER");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mot de Passe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Departement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
    return model;
}

QSqlQueryModel* Employer::trier(QString condition, bool ascendant) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString order = ascendant ? "ASC" : "DESC";

    if (condition == "nom") {
        model->setQuery("SELECT * FROM EMPLOYER ORDER BY NOM " + order);
    } else if (condition == "prenom") {
        model->setQuery("SELECT * FROM EMPLOYER ORDER BY PRENOM " + order);
    } else if (condition == "salaire") {
        model->setQuery("SELECT * FROM EMPLOYER ORDER BY SALAIRE " + order);
    }

    return model;
}

void Employer::recherche(int cin) {
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYER WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);

    if (query.exec() && query.next()) {
        nom = query.value("NOM").toString();
        prenom = query.value("PRENOM").toString();
        dateNaissance = query.value("DATE_NAISSANCE").toDate();
        salaire = query.value("SALAIRE").toDouble();
        motDePasse = query.value("MOT_DE_PASSE").toInt();
        departement = query.value("DEPARTEMENT").toString();
        poste = query.value("POSTE").toString();
    }
}

QMap<QString, int> Employer::statistiquesParDepartement() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT DEPARTEMENT, COUNT(*) FROM EMPLOYER GROUP BY DEPARTEMENT");
    while (query.next()) {
        QString dept = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[dept] = count;
    }
    return stats;
}
