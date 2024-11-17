#include "CalendarWidget.h"
#include <QCalendarWidget>
#include <QDate>
#include <QBrush>
#include <QPalette>
#include <QTextCharFormat>

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent)
{
    m_calendarWidget = new QCalendarWidget(this);
    m_calendarWidget->setWindowTitle("Calendrier");
    m_calendarWidget->show();
}

QCalendarWidget *CalendarWidget::getCalendarWidget() {
    return m_calendarWidget;
}

void CalendarWidget::markReservationDates(const QList<QDate> &dates)
{
    // Création d'une palette avec une couleur pour marquer les dates
    QBrush brush(Qt::green);  // Vous pouvez changer la couleur ici

    // Pour chaque date de la liste, marquer le jour dans le calendrier
    for (const QDate &date : dates) {
        // On applique la couleur à la date donnée
        m_calendarWidget->setDateTextFormat(date, QTextCharFormat());
        QTextCharFormat format;
        format.setBackground(brush);  // Définir la couleur de fond pour la date
        m_calendarWidget->setDateTextFormat(date, format);
    }
}
