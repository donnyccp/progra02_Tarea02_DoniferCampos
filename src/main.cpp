
#ifndef UNIT_TEST

#include "arbol.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    //Crear archivo .csv delimitado por comas
    fstream myFile;
    myFile.open("Reporte.csv", ios::out);

    //Abrir archivo personas
    std::ifstream ifsPersonas("Personas.txt", std::ifstream::in);
    if (!ifsPersonas.is_open())
    {
        std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
        return -1;
    }

    string lineaPersonas;
    string lineaNomina;
    string lineaHorasTrabajadas;
    string datosSalida;

    int idEmpleadoPersonas{0};
    string nombre{""};
    string apellido{""};
    string correo{""};
    int tipoEmpleado{0};
    int idSupervisor{0};

    int idEmpleadoNomina{0};
    float pagoMensualBruto{0.0};
    int idEmpleadoHorasTrabajadas{0};
    float montoPorHora{0.0};
    int horasLaboradas{0};
    string lineaEmpleado{""};

    float montoAPagar{0.0};
    string nombreEncargado{""};

    Arbol *arbol;
    new Arbol();

    while (std::getline(ifsPersonas, lineaPersonas))
    {

        try
        {
            // Procesamos la línea
            std::istringstream stream(lineaPersonas);
            idEmpleadoPersonas = 0;
            nombre = "";
            apellido = "";
            correo = "";
            tipoEmpleado = 0;
            idSupervisor = 0;

            stream >> idEmpleadoPersonas >> nombre >> apellido >> correo >> tipoEmpleado >> idSupervisor;

            // Revisar si es  el director
            if (idEmpleadoPersonas == 1)
            {
                std::ifstream ifsNomina("Nomina.txt", std::ifstream::in);
                if (!ifsNomina.is_open())
                {
                    std::cerr << "Error leyendo archivo Nomina.txt" << std::endl;
                    return -1;
                }

                while (std::getline(ifsNomina, lineaNomina))
                {

                    std::istringstream stream1(lineaNomina);
                    idEmpleadoNomina = 0;
                    pagoMensualBruto = 0.0;
                    stream1 >> idEmpleadoNomina >> pagoMensualBruto;

                    if (idEmpleadoPersonas == idEmpleadoNomina)
                    {

                        montoAPagar = pagoMensualBruto - pagoMensualBruto * 0.07;

                        datosSalida = idEmpleadoPersonas + "," + nombre + "," + apellido + "," + "Director" + "," + to_string(montoAPagar);
                    }
                }
                ifsNomina.close();
            }
            else
            {

                if (tipoEmpleado == 1)
                {
                    std::ifstream ifsNomina("Nomina.txt", std::ifstream::in);

                    if (!ifsNomina.is_open())
                    {
                        std::cerr << "Error leyendo archivo Nomina.txt" << std::endl;
                        return -1;
                    }
                    while (std::getline(ifsNomina, lineaNomina))
                    {
                        std::istringstream stream2(lineaNomina);

                        stream2 >> idEmpleadoNomina;
                        stream2 >> pagoMensualBruto;
                        if (idEmpleadoPersonas == idEmpleadoNomina)
                        {

                            montoAPagar = pagoMensualBruto - pagoMensualBruto * 0.07;

                            datosSalida = idEmpleadoPersonas + "," + nombre + "," + apellido + "," + "Director" + "," + to_string(montoAPagar);
                        }
                    }
                    ifsNomina.close();
                }
                else if (tipoEmpleado == 2)
                {
                    std::ifstream ifsHorasTrabajadas("HorasTrabajadas.txt", std::ifstream::in);
                    /* if (!ifsHorasTrabajadas.is_open())
                    {
                        std::cerr << "Error leyendo archivo HorasTrabajadas.txt" << std::endl;
                        return -1;
                    }*/
                    while (std::getline(ifsHorasTrabajadas, lineaHorasTrabajadas) && idEmpleadoPersonas != idEmpleadoHorasTrabajadas)
                    {
                        std::istringstream stream3(lineaHorasTrabajadas);
                        stream3 >> idEmpleadoHorasTrabajadas;
                        stream3 >> montoPorHora;
                        stream3 >> horasLaboradas;
                        if (idEmpleadoPersonas == idEmpleadoHorasTrabajadas)
                        {

                            montoAPagar = montoPorHora * horasLaboradas;

                            datosSalida = idEmpleadoPersonas + "," + nombre + "," + apellido + "," + "Director" + "," + to_string(montoAPagar);
                            cout <<datosSalida<<endl;
                        }
                    }
                    ifsHorasTrabajadas.close();
                }
            }
        }
        catch (string &excepcion)
        {
            cerr << excepcion << endl;
        }

        myFile << datosSalida << endl;
        arbol->AgregarNodo(idEmpleadoPersonas, idEmpleadoPersonas, idSupervisor);
        datosSalida = "";
    }
    myFile.close();

    ifsPersonas.close();

    std::cout << *arbol;
    delete arbol;

    return 0;
}
#endif
