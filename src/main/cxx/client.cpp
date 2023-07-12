#include "HelloApp.hh"

#include <CORBA.h>

#include <iostream>

int main(int argc, char *argv[])
{
    CORBA::ORB_ptr orb = nullptr;
    try
    {
        // create and initialise the ORB
        orb = CORBA::ORB_init(argc, argv);

        // get the root naming context
        auto root_nc = CosNaming::NamingContext::_narrow(orb->resolve_initial_references("NameService"));

        // resolve the object reference in naming
        CosNaming::Name name;
        name.length(1);
        name[0].id = "Hello";
        auto hello_impl = HelloApp::Hello::_narrow(root_nc->resolve(name));

        // invoke the object method
        std::cout << hello_impl->sayHello() << std::endl;
    }
    catch (CORBA::Exception &e)
    {
        std::cerr << "error: caught CORBA::" << e._name() << std::endl;
    }
    if (orb != nullptr)
    {
        orb->destroy();
    }
    return 0;
}
