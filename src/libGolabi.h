
#ifndef LIB_GOLABI
#define LIB_GOLABI

#define Struct(Name)          \
    struct Name;              \
    typedef struct Name Name; \
    struct Name

#define New(Type, Size) (Type *)malloc(sizeof(Type) * Size)

#endif