

#include "planilla.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Planilla::Planilla()
{
    resultado = "";
    datosSalida = "";
    lineaNomina = "";
    lineaHorasTrabajadas = "";
    idEmpleadoPersonas = 0;
    nombre = "";
    apellido = "";
    correo = "";
    tipoEmpleado = 0;
    idSupervisor = 0;

    idEmpleadoNomina = 0;
    pagoMensualBruto = 0.0;
    idEmpleadoHorasTrabajadas = 0;
    montoPorHora = 0.0;
    horasLaboradas = 0;
    lineaEmpleado = "";

    montoAPagarPlanilla = 0.0;
    impuestosPlanilla = 0.0;
}

string Planilla::calcularPlanillaPago(string linea)
{
    try
    {
        // Procesamos la línea
        lineaPersonas = linea;
        std::istringstream stream(lineaPersonas);
        idEmpleadoPersonas = 0;
        nombre = "";
        apellido = "";
        correo = "";
        tipoEmpleado = 0;
        idSupervisor = 0;

        stream >> idEmpleadoPersonas >> nombre >> apellido >> correo >> tipoEmpleado >> idSupervisor;

        if (idEmpleadoPersonas == 1)
        {
            // Revisar si es  el director

            std::ifstream ifsNomina("Nomina.txt", std::ifstream::in);
            /* if (!ifsNomina.is_open())
            {
                std::cerr << "Error leyendo archivo Nomina.txt" << std::endl;
                return -1;
            }*/

            while (std::getline(ifsNomina, lineaNomina))
            {

                std::istringstream stream1(lineaNomina);
                idEmpleadoNomina = 0;
                pagoMensualBruto = 0.0;
                stream1 >> idEmpleadoNomina >> pagoMensualBruto;

                if (idEmpleadoPersonas == idEmpleadoNomina)
                {

                    montoAPagarPlanilla = pagoMensualBruto - pagoMensualBruto * 0.07;
                    impuestosPlanilla = pagoMensualBruto * 0.07;
                    datosSalida = "";

                    datosSalida = to_string(idEmpleadoPersonas) + " " + nombre + " " + apellido + " " + "No" + " " + "Aplica" + " " + to_string(montoAPagarPlanilla) + " " + to_string(idEmpleadoPersonas) + " " + to_string(idSupervisor) + " " + to_string(impuestosPlanilla);
                }
            }
            ifsNomina.close();
        }
        else
        {
            if (tipoEmpleado == 1)
            {
                calcularPagoPorNomina(idEmpleadoPersonas, idSupervisor, nombre, apellido);
            }
            else
            {
                if (tipoEmpleado == 2)
                {
                    calcularPagoPorHorasTrabajadas(idEmpleadoPersonas, idSupervisor, nombre, apellido);
                }
            }
        }
    }
    catch (string &excepcion)
    {
        cerr << excepcion << endl;
    }
    return resultado = datosSalida;
}

string Planilla::calcularPagoPorNomina(int idE, int idS, string nombreE, string apellidoE)
{
    idEmpleadoPersonas = idE;
    idSupervisor = idS;
    nombre=nombreE;
    apellido=apellidoE;

    std::ifstream ifsNomina("Nomina.txt", std::ifstream::in);

    /* if (!ifsNomina.is_open())
    {
        std::cerr << "Error leyendo archivo Nomina.txt" << std::endl;
        return -1;
    }*/
    while (std::getline(ifsNomina, lineaNomina))
    {
        std::istringstream stream2(lineaNomina);

        stream2 >> idEmpleadoNomina;
        stream2 >> pagoMensualBruto;
        if (idEmpleadoPersonas == idEmpleadoNomina)
        {

            //Monto neto a pagar
            montoAPagarPlanilla = pagoMensualBruto - pagoMensualBruto * 0.07;
            //Calculo impuestos
            impuestosPlanilla = pagoMensualBruto * 0.07;

            //Buscar nombre de supervisor

            std::ifstream ifsNombreDeSupervisor("Personas.txt", std::ifstream::in);

            /*  if (!ifsNombreDeSupervisor.is_open())
            {
                std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
                return -1;
            }*/
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
                    datosSalida = "";
                    datosSalida = to_string(idEmpleadoPersonas) + " " + nombre + " " + apellido + " " + nombreSupervisor + " " + apellidoSupervisor + " " + to_string(montoAPagarPlanilla) + " " + to_string(idEmpleadoPersonas) + " " + to_string(idSupervisor) + " " + to_string(impuestosPlanilla);
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

    return resultado = datosSalida;
}

string Planilla::calcularPagoPorHorasTrabajadas(int idE, int idS, string nombreE, string apellidoE)
{
    idEmpleadoPersonas = idE;
    idSupervisor = idS;
    nombre=nombreE;
    apellido=apellidoE;
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
            montoAPagarPlanilla = montoPorHora * horasLaboradas;
            impuestosPlanilla = 0;

            //Buscar nombre de supervisor

            std::ifstream ifsNombreDeSupervisor("Personas.txt", std::ifstream::in);

            /* if (!ifsNombreDeSupervisor.is_open())
            {
                std::cerr << "Error leyendo archivo Personas.txt" << std::endl;
                return -1;
            }*/
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
                    datosSalida = "";
                    datosSalida = to_string(idEmpleadoPersonas) + " " + nombre + " " + apellido + " " + nombreSupervisor + " " + apellidoSupervisor + " " + to_string(montoAPagarPlanilla) + " " + to_string(idEmpleadoPersonas) + " " + to_string(idSupervisor) + " " + to_string(impuestosPlanilla);
                    
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

    return resultado = datosSalida;
}
