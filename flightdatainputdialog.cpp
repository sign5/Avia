#include "flightdatainputdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QDateTimeEdit>
#include <QDebug>

FlightDataInputDialog::FlightDataInputDialog(QWidget *parent, QString title) : QDialog(parent) {
    QFormLayout *formLayout = new QFormLayout(this);
    setWindowTitle(title);

    QLabel *lblFrom = new QLabel("Из точки", formLayout->widget());
    QLabel *lblTo = new QLabel("В точку", formLayout->widget());
    QLabel *lblPrice = new QLabel("Цена", formLayout->widget());
    QLabel *lblDeparture = new QLabel("Отправление", formLayout->widget());
    QLabel *lblArrival = new QLabel("Прибытие", formLayout->widget());

    QLineEdit *lineEditFrom = new QLineEdit(this);
    QLineEdit *lineEditTo = new QLineEdit(this);
    QLineEdit *lineEditPrice = new QLineEdit(this);
    QDateTimeEdit *dateTimeEditDeparture = new QDateTimeEdit(this);
    QDateTimeEdit *dateTimeEditArrival = new QDateTimeEdit(this);

    formLayout->addRow(lblFrom, lineEditFrom);
    formLayout->addRow(lblTo, lineEditTo);
    formLayout->addRow(lblPrice, lineEditPrice);
    formLayout->addRow(lblDeparture, dateTimeEditDeparture);
    formLayout->addRow(lblArrival, dateTimeEditArrival);

    fields << lineEditFrom;
    fields << lineEditTo;
    fields << lineEditPrice;
    fields << dateTimeEditDeparture;
    fields << dateTimeEditArrival;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    formLayout->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &FlightDataInputDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &FlightDataInputDialog::reject);
    Q_ASSERT(conn);

    setLayout(formLayout);
}

FlightDataInputDialog::FlightDataInputDialog(QWidget *parent, QStringList values, QString title) : QDialog(parent) {
    QFormLayout *formLayout = new QFormLayout(this);
    setWindowTitle(title);

    QLabel *lblFrom = new QLabel("Из точки", formLayout->widget());
    QLabel *lblTo = new QLabel("В точку", formLayout->widget());
    QLabel *lblPrice = new QLabel("Цена", formLayout->widget());
    QLabel *lblDeparture = new QLabel("Отправление", formLayout->widget());
    QLabel *lblArrival = new QLabel("Прибытие", formLayout->widget());

    QLineEdit *lineEditFrom = new QLineEdit(this);
    lineEditFrom->setText(values[0]);
    QLineEdit *lineEditTo = new QLineEdit(this);
    lineEditTo->setText(values[1]);
    QLineEdit *lineEditPrice = new QLineEdit(this);
    lineEditPrice->setText(values[2]);
    QDateTimeEdit *dateTimeEditDeparture = new QDateTimeEdit(this);
    dateTimeEditDeparture->setDateTime(QDateTime::fromString(values[3], "dd.MM.yyyy hh:mm"));
    QDateTimeEdit *dateTimeEditArrival = new QDateTimeEdit(this);
    dateTimeEditArrival->setDateTime(QDateTime::fromString(values[4], "dd.MM.yyyy hh:mm"));

    formLayout->addRow(lblFrom, lineEditFrom);
    formLayout->addRow(lblTo, lineEditTo);
    formLayout->addRow(lblPrice, lineEditPrice);
    formLayout->addRow(lblDeparture, dateTimeEditDeparture);
    formLayout->addRow(lblArrival, dateTimeEditArrival);

    fields << lineEditFrom;
    fields << lineEditTo;
    fields << lineEditPrice;
    fields << dateTimeEditDeparture;
    fields << dateTimeEditArrival;

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    formLayout->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &FlightDataInputDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &FlightDataInputDialog::reject);
    Q_ASSERT(conn);

    setLayout(formLayout);
}

QStringList FlightDataInputDialog::getStrings(QWidget *parent, QString title, bool *ok) {
    FlightDataInputDialog *dialog = new FlightDataInputDialog(parent, title);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            if (field->metaObject()->className() == QLineEdit().metaObject()->className()) {
                list << dynamic_cast<QLineEdit*>(field)->text();
            }
            if (field->metaObject()->className() == QDateTimeEdit().metaObject()->className()) {
                list << dynamic_cast<QDateTimeEdit*>(field)->dateTime().toString("dd.MM.yyyy hh:mm");
            }
        }
    }

    dialog->deleteLater();
    return list;
}

QStringList FlightDataInputDialog::getStrings(QWidget *parent, QStringList values, QString title, bool *ok) {
    FlightDataInputDialog *dialog = new FlightDataInputDialog(parent, values, title);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            if (field->metaObject()->className() == QLineEdit().metaObject()->className()) {
                list << dynamic_cast<QLineEdit*>(field)->text();
            }
            if (field->metaObject()->className() == QDateTimeEdit().metaObject()->className()) {
                list << dynamic_cast<QDateTimeEdit*>(field)->dateTime().toString("dd.MM.yyyy hh:mm");
            }
        }
    }

    dialog->deleteLater();
    return list;
}
