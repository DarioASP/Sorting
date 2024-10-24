#include <string>
#include <vector>

class Linea
{
private:
    std::string mes;
    int dia;
    std::string hora;
    std::string direccionIP;
    std::string mensaje;

public:
    Linea();
    Linea(std::string, int, std::string, std::string, std::string);
    std::string getMes();
    int getDia();
    std::string getHora();
    std::string getIP();
    std::string getMensaje();
    std::string to_string();
};