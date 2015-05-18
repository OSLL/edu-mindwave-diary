#include "values.h"

int Meditation = rand() % 100 - 20;
int Concentration = rand() % 100 - 20;

int getMeditationValue()
{
    Meditation += rand() % 5 - 2;
    return Meditation;
}

int getConcentrationValue()
{
    Concentration += rand() % 5 - 2;
    return Concentration;
}
