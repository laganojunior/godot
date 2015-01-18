#include "EnetWrapperSingleton.h"
#include <core/print_string.h>
#include <iostream>

EnetWrapperSingleton enet_wrapper_singleton;

EnetWrapperSingleton :: EnetWrapperSingleton()
{
    if (enet_initialize() != 0)
    {
        // How do you log errors in godot?
        std :: cout << "Error initializing enet wrapper" << std :: endl;
    }
    else
    {
        std :: cout << "Enet wrapper all good!" << std :: endl;
    }
}

EnetWrapperSingleton :: ~EnetWrapperSingleton()
{
    enet_deinitialize();
}
