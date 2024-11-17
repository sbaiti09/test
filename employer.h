#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Employer
{
    QString nom, prenom, departement, poste;
    QDate dateNaissance;
    double salaire;
    int motDePasse, cin;

public:
    Employer();
    Employer(QString, QString, QDate, double, int, QString, QString, int);

    int getCin() const { return cin; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QDate getDateNaissance() const { return dateNaissance; }
    double getSalaire() const { return salaire; }
    int getMotDePasse() const { return motDePasse; }
    QString getDepartement() const { return departement; }
    QString getPoste() const { return poste; }

    void setCin(int c) { cin = c; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setDateNaissance(QDate date) { dateNaissance = date; }
    void setSalaire(double s) { salaire = s; }
    void setMotDePasse(int mdp) { motDePasse = mdp; }
    void setDepartement(QString d) { departement = d; }
    void setPoste(QString p) { poste = p; }

    bool ajouter();
    bool supprimer(int cin);
    bool modifier(int cin);
    QSqlQueryModel* afficher();
    QSqlQueryModel* trier(QString condition, bool ascendant);
    void recherche(int cin);
    QMap<QString, int> statistiquesParDepartement();
};

#endif // EMPLOYER_H
