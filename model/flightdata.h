#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H
#include <QDateTime>

namespace Avia {
class FlightData
{
private:
    static int TOTAL_FLIGHT_COUNT;
    int id;
    int price;
    QDateTime departureDatetime;
    QDateTime arrivalDatetime;

public:
    FlightData(int price, QDateTime departureDatetime, QDateTime arrivalDatetime);
    int getId() const;
    int getPrice() const;
    void setPrice(int newPrice);
    QDateTime getDepartureDatetime() const;
    void setDepartureDatetime(const QDateTime &value);
    QDateTime getArrivalDatetime() const;
    void setArrivalDatetime(const QDateTime &value);
    ~FlightData();
};
}

#endif // FLIGHTDATA_H
