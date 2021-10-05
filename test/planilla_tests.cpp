#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;


#include "../src/planilla.h"
namespace
 {

     TEST(PlanillaTests, Test_calcularPlanillaPago) {
     
        Planilla planilla;
        std::string linea="1 Alberta Parra alberta_parra@biz.com 1 ";
        std::string actual = planilla.calcularPlanillaPago(linea);       
        EXPECT_EQ("1 Alberta Parra No Aplica 4278.911621 1 0 322.068604", actual);
     }
       
       TEST(PlanillaTests, Test_calcularPagoPorNomina) {
     
        Planilla planilla;        
        std::string actual = planilla.calcularPagoPorNomina(2, 1, "Jeannete", "Parra");
        EXPECT_EQ("2 Jeannete Parra Denis Tyler 2880.675049 2 1 216.824997", actual);
     }

       TEST(PlanillaTests, Test_calcularPagoPorHorasTrabajadas) {
     
        Planilla planilla;
        std::string actual = planilla.calcularPagoPorHorasTrabajadas(463, 22, "Fiorella", "Parra");
        EXPECT_EQ("463 Fiorella Parra Jacob Carter 583.300049 463 22 0.000000", actual);
     }
 }