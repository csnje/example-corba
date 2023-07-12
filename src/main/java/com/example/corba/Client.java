package com.example.corba;

import org.omg.CORBA.ORB;
import org.omg.CosNaming.NamingContextExtHelper;

import HelloApp.*;

public class Client {
    public static void main(String[] args) {
        ORB orb = null;
        try {
            // create and initialise the ORB
            orb = ORB.init(args, null);

            // get the root naming context
            var rootNC = NamingContextExtHelper.narrow(orb.resolve_initial_references("NameService"));

            // resolve the object reference in naming
            var helloImpl = HelloHelper.narrow(rootNC.resolve_str("Hello"));

            // invoke the object method
            System.out.println(helloImpl.sayHello());
        } catch (Exception e) {
            System.out.println("error: " + e);
            e.printStackTrace(System.out);
        }
        if (orb != null) {
            orb.destroy();
        }
    }
}
