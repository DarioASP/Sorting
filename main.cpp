/*
Santiago Patricio Gómez Ochoa | A01735171
Darío Alberto Sánchez Perzabal | A01738266

Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
Este código en C++ calcula la suma de los primeros n números naturales utilizando tres métodos diferentes: iterativo, recursivo y directo
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Linea.cpp"
using namespace std;
ifstream archivo;
vector<Linea> registros;
vector<string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
// Funcion para asociar un numero con el mes
int obtenerNumeroMes(string mes)
{
    for (int i = 0; i < meses.size(); i++)
    {
        if (meses[i] == mes)
        {
            return i + 1;
        }
    }
    return -1;
}
// Funcion para pasar las horas a segundos, lo cual facilita la comparación más adelante
int horaASegundos(string hora)
{
    int hour = stoi(hora.substr(0, 2));
    int minutos = stoi(hora.substr(3, 2));
    int seconds = stoi(hora.substr(6, 2));
    int segundos = (hour * 3600) + (minutos * 60) + seconds;
    return segundos;
}
// Funcion para comparar direcciones ip
int ipANumero(string ip)
{
    size_t pos = ip.find('.');
    int octeto = stoi(ip.substr(0, pos));
    return octeto;
}
// Función para particionar el arreglo
int particion(vector<Linea> &arr, int inicio, int fin)
{
    int pivote = obtenerNumeroMes(arr[fin].getMes()); // Elegimos el último elemento como pivote
    int i = inicio - 1;                               // Índice del elemento más pequeño

    // Recorre el arreglo desde low hasta high - 1
    for (int j = inicio; j < fin; j++)
    {
        int c = obtenerNumeroMes(arr[j].getMes());
        if (c < pivote)
        {
            i++;
            swap(arr[i], arr[j]);
        }
        else if (c == pivote)
        {
            // Comparación de días
            if (arr[j].getDia() < arr[fin].getDia())
            {
                i++;
                swap(arr[i], arr[j]);
            }
            // Comparación de horas convertidas a segundos
            else if (arr[j].getDia() == arr[fin].getDia() && horaASegundos(arr[j].getHora()) < horaASegundos(arr[fin].getHora()))
            {
                i++;
                swap(arr[i], arr[j]);
            }
            // Comparación de IP si los días y horas son iguales
            else if (arr[j].getDia() == arr[fin].getDia() && horaASegundos(arr[j].getHora()) == horaASegundos(arr[fin].getHora()) && ipANumero(arr[j].getIP()) < ipANumero(arr[fin].getIP()))
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
    }
    swap(arr[i + 1], arr[fin]); // Coloca el pivote en su posición final
    return i + 1;               // Devuelve la posición del pivote
}

// Función recursiva de QuickSort
void quickSort(vector<Linea> &arr, int low, int high)
{
    if (low < high)
    {                                       // Condición para continuar la recursión
        int pi = particion(arr, low, high); // Encuentra el índice de partición
        quickSort(arr, low, pi - 1);        // Ordena la sublista izquierda
        quickSort(arr, pi + 1, high);       // Ordena la sublista derecha
    }
}

int main()
{
    // Crear un objeto ifstream para manejar el archivo
    archivo.open("bitacora.txt", ios::in);
    string renglon;
    string mes;
    int dia;
    string hora;
    string direccionIP;
    string mensaje;
    int Mesinicio, mesFin;
    string diaInicio, diaFin;
    while (!archivo.eof())
    {
        getline(archivo, renglon);
        // mes
        size_t pos = renglon.find(' ');
        mes = renglon.substr(0, pos);
        renglon.erase(0, pos + 1);
        pos = renglon.find(' ');
        // dia
        dia = stoi(renglon.substr(0, pos));
        renglon.erase(0, pos + 1);
        // hora
        pos = renglon.find(' ');
        hora = renglon.substr(0, pos);
        renglon.erase(0, pos + 1);
        // Direccion IP
        pos = renglon.find(' ');
        direccionIP = renglon.substr(0, pos);
        renglon.erase(0, pos + 1);
        // Mensaje
        mensaje = renglon;
        Linea l(mes, dia, hora, direccionIP, mensaje);
        registros.push_back(l);
    }
    archivo.close();
    quickSort(registros, 0, registros.size() - 1);
    cout << "Mes de inicio" << endl;
    cin >> Mesinicio;
    cout << "Dia de inicio " << endl;
    cin >> diaInicio;
    cout << "Mes fin " << endl;
    cin >> mesFin;
    cout << "Dia fin " << endl;
    cin >> diaFin;

    if (stoi(diaInicio) < 10 && diaInicio[0] != '0')
        diaInicio = "0" + diaInicio;

    string input = to_string(Mesinicio) + diaInicio;

    int inicio = stoi(input);

    if (stoi(diaFin) < 10 && diaFin[0] != '0')
        diaFin = "0" + diaFin;

    string inputfinal = to_string(mesFin) + diaFin;
    int final = stoi(inputfinal);
    if (inicio > final)
        cerr << "El mes de inicio no puede ser mayor que el mes de fin";
    // CREAR ARCHIVO DE SALIDA
    ofstream salida("sorted.txt");
    // ofstream depuera("depura.txt");
    for (int i = 0; i < registros.size(); i++)
    {
        salida << registros[i].to_string() << endl;
    };
    for (int i = 0; i < registros.size(); i++)
    {

        int mesRegistro = obtenerNumeroMes(registros[i].getMes());
        string diaRegistro = to_string(registros[i].getDia());

        if (stoi(diaRegistro) < 10 && diaRegistro[0] != '0')
        {
            diaRegistro = "0" + diaRegistro;
        }
        string comparador = to_string(mesRegistro) + diaRegistro;

        int intcomparador = stoi(comparador);

        if (inicio <= intcomparador && intcomparador <= final)
        {
            // depura << mesRegistro << " : " << diaRegistro << endl;
            cout << registros[i].to_string() << endl;
        }
    }
}