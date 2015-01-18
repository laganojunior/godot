#include "EnetWrapperSingleton.h"
#include <core/print_string.h>
#include <iostream>

EnetWrapperSingleton enet_wrapper_singleton;

EnetWrapperSingleton :: EnetWrapperSingleton()
{
    if (enet_initialize() != 0)
    {
        // How do you log errors in godot?
        print_line("Error initializing enet wrapper");
    }
    else
    {
        print_line("Initialized Enet?");
    }
}

EnetWrapperSingleton :: ~EnetWrapperSingleton()
{
    enet_deinitialize();
}
