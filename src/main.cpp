
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
    float subtotal{0.0};
    float impuestos{0.0};
    float total{0.0};

    //Crear arbol
    Arbol *arbol = new Arbol();

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
                        impuestos = impuestos + pagoMensualBruto * 0.07;

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

                            //Monto neto a pagar
                            montoAPagar = pagoMensualBruto - pagoMensualBruto * 0.07;
                            //Calculo impuestos
                            impuestos = impuestos + pagoMensualBruto * 0.07;

                            //Buscar nombre de supervisor

                            std::ifstream ifsNombreDeSupervisor("Personas.txt", std::ifstream::in);

                            if (!ifsNombreDeSupervisor.is_open())
                            {
                                std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
                                return -1;
                            }
                            string lineaNombreSupervisor{""};
                            string nombreCompletoSupervisor{""};
                            int idEmpleadoSupervisor{0};
                            string correoSupervisor{""};
                            int tipoEmpleadoSupervisor{0};
                            string nombreSupervisor{""};
                            string apellidoSupervisor{""};

                            while (std::getline(ifsNombreDeSupervisor, lineaNombreSupervisor) && idEmpleadoSupervisor != idSupervisor)
                            {

                                try
                                {
                                    // Procesamos la línea
                                    std::istringstream stream4(lineaNombreSupervisor);
                                    idEmpleadoSupervisor = 0;
                                    nombreSupervisor = "";
                                    apellidoSupervisor = "";
                                    correoSupervisor = "";
                                    tipoEmpleadoSupervisor = 0;

                                    stream4 >> idEmpleadoSupervisor >> nombreSupervisor >> apellidoSupervisor >> correoSupervisor >> tipoEmpleadoSupervisor >> idEmpleadoSupervisor;

                                    datosSalida = idEmpleadoPersonas + "," + nombre + "," + apellido + "," + nombreSupervisor + "," + apellidoSupervisor + "," + to_string(montoAPagar);
                                }
                                catch (string &excepcion)
                                {
                                    cerr << excepcion << endl;
                                }
                            }

                            ifsNombreDeSupervisor.close();
                        }
                    }
                    ifsNomina.close();
                }
                else
                {
                    if (tipoEmpleado == 2)
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

                                //Monto neto a pagar
                                montoAPagar = montoPorHora * horasLaboradas;

                                //Buscar nombre de supervisor

                                std::ifstream ifsNombreDeSupervisor("Personas.txt", std::ifstream::in);

                                if (!ifsNombreDeSupervisor.is_open())
                                {
                                    std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
                                    return -1;
                                }
                                string lineaNombreSupervisor{""};
                                string nombreCompletoSupervisor{""};
                                int idEmpleadoSupervisor{0};
                                string correoSupervisor{""};
                                int tipoEmpleadoSupervisor{0};
                                string nombreSupervisor{""};
                                string apellidoSupervisor{""};

                                while (std::getline(ifsNombreDeSupervisor, lineaNombreSupervisor) && idEmpleadoSupervisor != idSupervisor)
                                {

                                    try
                                    {
                                        // Procesamos la línea
                                        std::istringstream stream4(lineaNombreSupervisor);
                                        idEmpleadoSupervisor = 0;
                                        nombreSupervisor = "";
                                        apellidoSupervisor = "";
                                        correoSupervisor = "";
                                        tipoEmpleadoSupervisor = 0;

                                        stream4 >> idEmpleadoSupervisor >> nombreSupervisor >> apellidoSupervisor >> correoSupervisor >> tipoEmpleadoSupervisor >> idEmpleadoSupervisor;

                                        datosSalida = idEmpleadoPersonas + "," + nombre + "," + apellido + "," + nombreSupervisor + "," + apellidoSupervisor + "," + to_string(montoAPagar);
                                    }
                                    catch (string &excepcion)
                                    {
                                        cerr << excepcion << endl;
                                    }
                                }

                                ifsNombreDeSupervisor.close();
                            }
                        }
                        ifsHorasTrabajadas.close();
                    }
                }
            }
        }
        catch (string &excepcion)
        {
            cerr << excepcion << endl;
        }

        myFile << datosSalida << endl;
        //Calculo subtotal y totales
        subtotal = subtotal + montoAPagar;
        total = subtotal + impuestos;

        arbol->AgregarNodo(idEmpleadoPersonas, idEmpleadoPersonas, idSupervisor);
        datosSalida = "";
    }
    myFile << "Subtotal:" << subtotal << endl;
    myFile << "Impuestos:" << impuestos << endl;
    myFile << "Total:" << total << endl;

    myFile.close();

    ifsPersonas.close();

    std::cout << *arbol;
    delete arbol;

    return 0;
}
#endif
