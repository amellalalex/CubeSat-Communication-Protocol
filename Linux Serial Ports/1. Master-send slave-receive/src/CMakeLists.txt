cmake_minimum_required(VERSION 2.6)

project("LinuxSerialPorts1")

set ( src-files
  main.c
  master.c
  slave.c
)

add_executable("pseudo-terminal" ${src-files})
