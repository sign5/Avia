#include "flightdata.h"

int Avia::FlightData::TOTAL_FLIGHT_COUNT = 0;

Avia::FlightData::FlightData(int price, QDateTime departureDatetime, QDateTime arrivalDatetime) {
    FlightData::TOTAL_FLIGHT_COUNT++;
    this->id = TOTAL_FLIGHT_COUNT;
    this->price = price;
    this->departureDatetime = departureDatetime;
    this->arrivalDatetime = arrivalDatetime;
}

int Avia::FlightData::getId() const {
    return id;
}

int Avia::FlightData::getPrice() const {
    return price;
}

void Avia::FlightData::setPrice(int value) {
    price = value;
}

QDateTime Avia::FlightData::getDepartureDatetime() const {
    return departureDatetime;
}

void Avia::FlightData::setDepartureDatetime(const QDateTime &value) {
    departureDatetime = value;
}

QDateTime Avia::FlightData::getArrivalDatetime() const {
    return arrivalDatetime;
}

void Avia::FlightData::setArrivalDatetime(const QDateTime &value) {
    arrivalDatetime = value;
}

Avia::FlightData::~FlightData() {}
