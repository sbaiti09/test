#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Transactions
{
private:
    QString compte_ass, type_tr, date_tr, categorie_tr, mode_paiement, description, id_emp;
    double montant_tr;

public:
    Transactions();  // Constructeur par défaut
    Transactions(QString compte_ass, QString type_tr, QString date_tr, QString categorie_tr,
                 double montant_tr, QString mode_paiement, QString description, QString id_emp);

    // Accesseurs (Getters)
    QString getCompteAss() const { return compte_ass; }
    QString getTypeTr() const { return type_tr; }
    QString getDateTr() const { return date_tr; }
    QString getCategorieTr() const { return categorie_tr; }
    double getMontantTr() const { return montant_tr; }
    QString getModePaiement() const { return mode_paiement; }
    QString getDescription() const { return description; }
    QString getIdEmp() const { return id_emp; }

    // Mutateurs (Setters)
    void setCompteAss(const QString& c) { compte_ass = c; }
    void setTypeTr(const QString& t) { type_tr = t; }
    void setDateTr(const QString& d) { date_tr = d; }
    void setCategorieTr(const QString& cat) { categorie_tr = cat; }
    void setMontantTr(double m) { montant_tr = m; }
    void setModePaiement(const QString& mode) { mode_paiement = mode; }
    void setDescription(const QString& desc) { description = desc; }
    void setIdEmp(const QString& emp) { id_emp = emp; }

    bool ajouter();
    bool supprimer(int id_tr);
    bool modifier(int id_tr);
    QSqlQueryModel* afficher();
    void rechercherParId(int id_tr);
    QSqlQueryModel* rechercher(const QString& critere, const QString& valeur);
    QSqlQueryModel* trier(const QString& condition, bool ascendant);
    QMap<QString, int> statistiquesParTypeEtCategorie();
};

#endif // TRANSACTIONS_H
