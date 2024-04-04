## About

Example use of [**Common Object Request Broker Architecture (CORBA)**](https://www.corba.org/).

## Build

### **Java** Build

The **Java** example uses [**Eclipse Glassfish ORB**](https://projects.eclipse.org/projects/ee4j.orb).

To build and package the **Java** code using [**Maven**](https://maven.apache.org/):
```bash
mvn package
```

### **C++** Build

The **C++** example uses [**omniORB**](https://www.omniorb-support.com/).
To install the **omniORB** dependencies on **Ubuntu** and derivatives:
```bash
sudo apt install libomniorb4-dev omniidl
```

To build the **C++** code using [**CMake**](https://cmake.org/).
```bash
mkdir target; cd target
cmake ..
cmake --build .
```

## Run

### Naming Service

A **CORBA** *naming service* is required; **CORBA** *servers* and **CORBA** *clients* register and lookup objects there.
Various *naming service* options can be used, including:
|Provided by|Command|Notes|
|---|---|---|
|[**Java 8**](https://docs.oracle.com/javase/8/docs/technotes/guides/idl/index.html) (or earlier) [`orbd`](https://docs.oracle.com/javase/8/docs/technotes/tools/unix/orbd.html)|`orbd -ORBInitialPort 1050`|transient and persistent naming service; creates a directory for persistent files at `./orb.db` by default|
|[**Java 8**](https://docs.oracle.com/javase/8/docs/technotes/guides/idl/index.html) (or earlier) [`tnameserv`](https://docs.oracle.com/javase/8/docs/technotes/tools/unix/tnameserv.html)|`tnameserv -ORBInitialPort 1050`|transient naming service|
|[**omniORB**](https://www.omniorb-support.com/) [`omniNames`](https://www.omniorb-support.com/omni43/omniNames.html)|`mkdir omniorb; omniNames -start 1050 -always -datadir omniorb -ORBsupportBootstrapAgent 1`|using a directory for persistent files at `./omniorb` and enables the Java bootstrap agent ([ref](https://omniorb.sourceforge.io/omni42/omniORB/omniORB004.html))|

### Server

The servers implement the same functionality, so run only one.

To run a server:
|Language|Command|
|---|---|
|**Java**|`java -cp "target/*:target/dependency/*" com.example.corba.Server -ORBInitialHost localhost -ORBInitialPort 1050`|
|**C++**|`target/server -ORBbootstrapAgentHostname localhost -ORBbootstrapAgentPort 1050`|

### Client

To run a client:
|Language|Command|
|---|---|
|**Java**|`java -cp "target/*:target/dependency/*" com.example.corba.Client -ORBInitialHost localhost -ORBInitialPort 1050`|
|**C++**|`target/client -ORBbootstrapAgentHostname localhost -ORBbootstrapAgentPort 1050`|

## References

Although **CORBA** was deprectated in **Java 9** and removed in **Java 11** ([ref](https://openjdk.org/jeps/320)), the [**Java SE 8** Java IDL (CORBA)](https://docs.oracle.com/javase/8/docs/technotes/guides/idl/index.html) documentation is still relevant.

[**Eclipse Glassfish ORB**](https://projects.eclipse.org/projects/ee4j.orb) is a drop in replacement for the removed **Java** standard library implementation of **CORBA**.

The [CORBA IDL Compiler Maven Plugin](https://www.mojohaus.org/idlj-maven-plugin/) for [**Maven**](https://maven.apache.org/) generates **CORBA** source code from [Interface Definition Language (**IDL**)](https://www.omg.org/spec/IDL/) files by invoking various code generators.
