# Server

## How to install

The installation should be pretty simple,
you will require to have Docker:
> https://docs.docker.com/engine/installation/

and Docker-Compose (version 2):
> https://docs.docker.com/compose/install/

## Database configuration

The database is hosted and configured in a docker's container.
You can find the SQL script used to generate the database at:
> ./resources/init.sql

But you shouldn't have to use it.

## Assumptions

In the current project, I assumed the clients' computers:
- were safe and thrusted
- their key were unique
- isn't on a specific Operating System
- HTTP header's weren't required.

## Requirements not covered

There are some requirements which haven't been covered:
- I don't use an HTTP protocol
- The smtp server doesn't send the emails

## How to build

Your only task would be to launch docker:
> docker-compose up standalone

## Issues

I faced several issues, slowing down the development progress:
- hardness to find a good library
- configuration issues with smtp container

## Feedback

The exercise is really good and the project is well designed
to try several fields. But it would have been bettter to have
a configured environment (DBMS, SMTP server).

I actually spent a huge amount of my time configuring the infrastructure
instead of developing the software and the communication itself.
And I assume those parts aren't really in the scope of the exercise.

Scaling the project to a 2 days project instead of 3 would be better,
specially if you have to work.

# Client

## How to install

The installation will be a bit more troublesome than for the server.
The Cmake is currently configured to work on Mac and UNIX
but the project should be independant.

Firstly you should install cmake (version 3 at least):
> https://cmake.org/

The project require to have C++ (version 11 at least):
> https://gcc.gnu.org/

For the network communication, you will need ZeroMQ (version 3 at least):
> http://zeromq.org/area:download

And its CPP's binding:
> https://github.com/zeromq/zmqpp

For the serialization the message, you will require the google ProtocolBuffer:
> https://developers.google.com/protocol-buffers/

To analyse the computer's system in any platform,
you will need to build and install Sigar API:
> https://github.com/hyperic/sigar 

And finally, for the unit tests, I used GoogleTest library:
> https://github.com/google/googletest

Of course, the installation will depends of your current Operating System,
if you can use the package manager from your Operating System, feel free to use it
(but be careful to take the development version).
Otherwise, you should be able to build the project from their github.

I wish you good luck for the installation part !

## Database configuration

There aren't any database for this project.

## Assumptions

In the current project, I assumed the clients' computers:
- were safe and thrusted
- their key were unique
- isn't on a specific Operating System
- HTTP headers weren't required

## Requirements not covered

There are one requirement which hasn't been covered:
- I don't use an HTTP protocol
- The messages and errors aren't logged.

## How to build

To build the project, I would recommand to follow those step:
> mkdir build

> cd build/

> cmake ..

> make

## Issues

The main issue was to find a good cross platform library to analyse the system.
And actually the Sigar API's website was down.

## Feedback

A good project, maybe specifying in the requirements if the project
must be cross platform or platform specific. I did waste a bit of time wondering for which platform to develop.

Scaling the project to a 2 days project instead of 3 would be better,
specially if you have to work.