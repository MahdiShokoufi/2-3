# {Name}.h Conventions:
Structs should be defined by Struct(Name) macro in libGolabi.h
Should contain definition for all functions in {Name}.c
Global variables Should be considered in two states : MAIN defined ⇒ real declaration; else ⇒ extern definition;


# {Name}.c Conventions:
Only {Name}.h inlcude
every function should have atleast one input type from {Name}.h


# {Main}.c Conventions:
Should define MAIN macro