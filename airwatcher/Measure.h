/*************************************************************************
                           Measure  -  description
                             -------------------
    copyright            : (C) OUIDAN SAAD, FADILI ZINEB, RISTOVSKI STEFAN, TUOYUAN TAN, HE MUYE
*************************************************************************/

//---------- Interface de la classe <Measure> (fichier Measure.h) ----------------
#if ! defined ( Measure_H )
#define Measure_H

#include <time.h>
#include"MeasureType.h"



class Measure
{
//----------------------------------------------------------------- PUBLIC

public:

  Measure ( );

  Measure(tm Timestamp, float value, MeasureType mt, string sensId);

//getters
    tm getTime();

    MeasureType getMeasureType();

    float getValue();

    string getSensorID();

//setters
    void setTime(tm time);

    void setValue(float value);

    void setMeasureType(MeasureType mt);

    virtual ~Measure ( );

//------------------------------------------------------------------ PRIVE

protected:

tm Timestamp;
float value;
MeasureType mt;
string sensorID;

};

#endif // Measure_H
