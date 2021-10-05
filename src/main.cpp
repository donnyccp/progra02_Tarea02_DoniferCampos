
#ifndef UNIT_TEST

#include "arbol.h"
#include "planilla.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    string lineaPersonas;
    string datosSalida;

    string nombre{""};
    string apellido{""};
    string nombreSupervisor{""};
    string apellidoSupervisor{""};
    float montoAPagarEmpleado{0.0};
    int idEmpleadoPersonas{0};
    int idSupervisor{0};
    float impuestosEmpleado{0.0};

    float montoAPagar{0.0};
    float subtotal{0.0};
    float impuestos{0.0};
    float total{0.0};

    //Crear archivo .csv delimitado por comas
    fstream myFile;
    myFile.open("Reporte.csv", ios::out);

    //Crear arbol
    Arbol *arbol = new Arbol();

    Planilla planillita;

    //Abrir archivo personas
    std::ifstream ifsPersonas("Personas.txt", std::ifstream::in);
    if (!ifsPersonas.is_open())
    {
        std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
        return -1;
    }

    while (std::getline(ifsPersonas, lineaPersonas))
    {

        datosSalida = "";
        apellidoSupervisor = "";
        idEmpleadoPersonas = 0;
        impuestosEmpleado = 0.0;
        montoAPagarEmpleado = 0.0;
        datosSalida = planillita.calcularPlanillaPago(lineaPersonas);

        std::istringstream ss(datosSalida);
        ss >> idEmpleadoPersonas >> nombre >> apellido >> nombreSupervisor >> apellidoSupervisor >> montoAPagarEmpleado >> idEmpleadoPersonas >> idSupervisor >> impuestosEmpleado;

        //Calculo subtotal y totales
        subtotal = subtotal + montoAPagarEmpleado;
        impuestos = impuestos + impuestosEmpleado;
        total = subtotal + impuestos;
        myFile << nombre << "," << apellido << "," << nombreSupervisor << "," << apellidoSupervisor << "," << montoAPagarEmpleado << endl;

        arbol->AgregarNodo(idEmpleadoPersonas, idEmpleadoPersonas, idSupervisor);

        datosSalida = "";
    }

    //Agregar subtotal, impuestos y total al archivo csv

    myFile << "Subtotal:" << subtotal << endl;
    myFile << "Impuestos:" << impuestos << endl;
    myFile << "Total:" << total << endl;

    myFile.close();

    ifsPersonas.close();
//Imprimir arbol relacion empleado y surpervisor
    std::cout << *arbol;
    delete arbol;

    return 0;
}
#endif
