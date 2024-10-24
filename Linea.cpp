#include "Linea.h"

Linea::Linea() : mes(""), dia(0), hora(""), direccionIP(""), mensaje("") {}

Linea::Linea(std::string mes, int dia, std::string hora, std::string direccionIP, std::string mensaje)
    : mes(mes), dia(dia), hora(hora), direccionIP(direccionIP), mensaje(mensaje) {}

std::string Linea::getMes()
{
    return mes;
}

int Linea::getDia()
{
    return dia;
}

std::string Linea::getHora()
{
    return hora;
}

std::string Linea::getIP()
{
    return direccionIP;
}

std::string Linea::getMensaje()
{
    return mensaje;
}

std::string Linea::to_string()
{
    return mes + " " + std::to_string(dia) + " " + hora + " " + direccionIP + " " + mensaje;
}
