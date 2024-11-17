#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QList>
#include <QDate>

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = nullptr);
    QCalendarWidget *getCalendarWidget();  // Méthode pour obtenir le widget calendrier
    void markReservationDates(const QList<QDate> &dates);  // Méthode pour marquer les dates

private:
    QCalendarWidget *m_calendarWidget;
};

#endif // CALENDARWIDGET_H
