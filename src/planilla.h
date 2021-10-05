#ifndef PLANILLA_H
#define PLANILLA_H

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Planilla {

    string resultado;
    string datosSalida;
    string lineaPersonas;
    string lineaNomina;
    string lineaHorasTrabajadas;
  
    int idEmpleadoPersonas;
    string nombre;
    string apellido;
    string correo;
    int tipoEmpleado;
    int idSupervisor;

    int idEmpleadoNomina;
    float pagoMensualBruto;
    int idEmpleadoHorasTrabajadas;
    float montoPorHora;
    int horasLaboradas;
    string lineaEmpleado;

    float montoAPagarPlanilla;
    float impuestosPlanilla;

    public:
    
        
    Planilla();

    string calcularPlanillaPago(string linea);
    string calcularPagoPorNomina(int idEmpleado, int idSupervisor, string nombreEmpleado, string apellidoEmpleado);
    string calcularPagoPorHorasTrabajadas(int idEmpleado, int idSupervisor, string nombreEmpleado, string apellidoEmpleado);
    
    
};

#endif