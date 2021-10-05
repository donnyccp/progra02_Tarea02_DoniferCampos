#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "../src/arbol.h"

namespace {
    TEST(ArbolTests, Test_Constructor) {
        Arbol *arbol = new Arbol();
        arbol->AgregarNodo(1, 1, 0);

        std::ostringstream streamSalida {};
        streamSalida << *arbol;
        std::string actual = streamSalida.str();

        delete arbol;

        EXPECT_EQ("Nodo: 1. Valor: 1\n", actual);
    }

    TEST(ArbolTests, Test_Agregar_Nodo) {
        Arbol *arbol = new Arbol();
        arbol->AgregarNodo(1, 1, 0);
        arbol->AgregarNodo(2, 2, 1); 
        arbol->AgregarNodo(3, 3, 2);       

        std::ostringstream streamSalida {};
        streamSalida << *arbol;
        std::string actual = streamSalida.str();

        delete arbol;

        std::ostringstream streamSalidaEsperada {};
        streamSalidaEsperada << "Nodo: 1. Valor: 1" << std::endl;
        streamSalidaEsperada << "Nodo: 2. Valor: 2" << std::endl;
        streamSalidaEsperada << "Nodo: 3. Valor: 3" << std::endl;
        std::string esperada = streamSalidaEsperada.str();

        EXPECT_EQ(esperada, actual);
    }

    TEST(ArbolTests, Test_Agregar_Nodos_UnNivel) {
        Arbol *arbol = new Arbol();
        arbol->AgregarNodo(1, 1, 0);
        arbol->AgregarNodo(2, 2, 1);        
        arbol->AgregarNodo(3, 3, 1);

        std::ostringstream streamSalida {};
        streamSalida << *arbol;
        std::string actual = streamSalida.str();

        delete arbol;

        std::ostringstream streamSalidaEsperada {};
        streamSalidaEsperada << "Nodo: 1. Valor: 1" << std::endl;
        streamSalidaEsperada << "Nodo: 2. Valor: 2" << std::endl;
        streamSalidaEsperada << "Nodo: 3. Valor: 3" << std::endl;
        std::string esperada = streamSalidaEsperada.str();

        EXPECT_EQ(esperada, actual);
    }
    
    TEST(ArbolTests, Test_Agregar_Nodos_DosNiveles) {
        Arbol *arbol = new Arbol();
        arbol->AgregarNodo(1, 1, 0);
        arbol->AgregarNodo(2, 2, 1);
        arbol->AgregarNodo(3, 5, 1);
        arbol->AgregarNodo(4, 5, 3);
        arbol->AgregarNodo(5, 5, 3);

        std::ostringstream streamSalida {};
        streamSalida << *arbol;
        std::string actual = streamSalida.str();

        delete arbol;

        std::ostringstream streamSalidaEsperada {};
        streamSalidaEsperada << "Nodo: 1. Valor: 1" << std::endl;
        streamSalidaEsperada << "Nodo: 2. Valor: 2" << std::endl;
        streamSalidaEsperada << "Nodo: 3. Valor: 5" << std::endl;
        streamSalidaEsperada << "Nodo: 4. Valor: 5" << std::endl;
        streamSalidaEsperada << "Nodo: 5. Valor: 5" << std::endl;
        std::string esperada = streamSalidaEsperada.str();

        EXPECT_EQ(esperada, actual);
    }

    

}