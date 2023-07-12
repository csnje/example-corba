#include "HelloApp.hh"

#include <CORBA.h>

#include <iostream>

class HelloImpl : public POA_HelloApp::Hello
{
public:
    inline HelloImpl() = default;
    virtual ~HelloImpl() = default;
    virtual char *sayHello();
};

char *HelloImpl::sayHello()
{
    return CORBA::string_dup("Hello, World!");
}

int main(int argc, char *argv[])
{
    CORBA::ORB_ptr orb = nullptr;
    try
    {
        // create and initialise the ORB
        orb = CORBA::ORB_init(argc, argv);

        // get reference to RootPOA and activate the POAManager
        auto root_poa = PortableServer::POA::_narrow(orb->resolve_initial_references("RootPOA"));
        root_poa->the_POAManager()->activate();

        // create the servant and get object reference from the servant
        auto servant = new HelloImpl();
        auto servant_ref = servant->_this();

        // get the root naming context
        auto root_nc = CosNaming::NamingContext::_narrow(orb->resolve_initial_references("NameService"));

        // bind the object reference in naming
        CosNaming::Name name;
        name.length(1);
        name[0].id = "Hello";
        root_nc->rebind(name, servant_ref);

        std::cout << "Server ready" << std::endl;

        orb->run();
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
