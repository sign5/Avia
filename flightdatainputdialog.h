#ifndef FLIGHTDATAINPUTDIALOG_H
#define FLIGHTDATAINPUTDIALOG_H

#include <QDialog>

class QLineEdit;
class QLabel;

class FlightDataInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FlightDataInputDialog(QWidget *parent = nullptr, QString title = "Input");
    explicit FlightDataInputDialog(QWidget *parent = nullptr, QStringList values = QStringList(), QString title = "Input");

    static QStringList getStrings(QWidget *parent, QString title, bool *ok = nullptr);

    static QStringList getStrings(QWidget *parent, QStringList values, QString title, bool *ok = nullptr);

private:
    QList<QWidget*> fields;
};

#endif // FLIGHTDATAINPUTDIALOG_H
