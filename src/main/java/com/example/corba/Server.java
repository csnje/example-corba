package com.example.corba;

import org.omg.CORBA.ORB;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContextExtHelper;
import org.omg.PortableServer.POAHelper;

import HelloApp.*;

class HelloImpl extends HelloPOA {
    public String sayHello() {
        return "Hello, World!";
    }
}

public class Server {
    public static void main(String[] args) {
        ORB orb = null;
        try {
            // create and initialise the ORB
            orb = ORB.init(args, null);

            // get reference to RootPOA and activate the POAManager
            var rootPOA = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
            rootPOA.the_POAManager().activate();

            // create the servant and get object reference from the servant
            var servantRef = HelloHelper.narrow(rootPOA.servant_to_reference(new HelloImpl()));

            // get the root naming context
            var rootNC = NamingContextExtHelper.narrow(orb.resolve_initial_references("NameService"));

            // bind the object reference in naming
            NameComponent path[] = rootNC.to_name("Hello");
            rootNC.rebind(path, servantRef);

            System.out.println("Server ready");

            orb.run();
        } catch (Exception e) {
            System.out.println("error: " + e);
            e.printStackTrace(System.out);
        }
        if (orb != null) {
            orb.destroy();
        }
    }
}
