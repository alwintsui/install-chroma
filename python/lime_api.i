//directors="1"
%module (docstring="CLime C++ wrapper in Python, May. 2025, Shun Xu <xushun@sccas.cn>") pylime
%{

extern "C"
{
#include "lime_defs.h"
#include "lime_utils.h"
}
#include "clime_writer.h"
#include "clime_reader.h"
#include "clime_utils.h"

#define SWIG_FILE_WITH_INIT

%}

%warnfilter(305, 325, 389, 401, 451, 462, 503);
//Warning 389: operator[] ignored (consider using %extend)
//Warning 451: Setting a const char * variable may leak memory.
//Warning 325: Nested union not currently supported (union_int_float_t,Param ignored)
//Warning 462: Unable to set dimensionless array variable
//Warning 305: Bad constant value (ignored).
//Warning 503: Can't wrap 'operator double*' unless renamed to a valid identifier.
//Warning 401: Nothing known about base class 'std::enable_shared_from_this< MechSlot >'. Ignored.

#ifdef SWIGPYTHON

//defined before %include file headers
%rename(__assign__) *::operator=;
//disable in wlc_types.h

%include "typemaps.i"
%include "factory.i"
//string,vector,map,pair
%include "stl.i" 
/* instantiate the required template specializations */
%define %vector_ext(TYPE)
%template(vector_##TYPE) std::vector<TYPE>;
%extend std::vector<TYPE> {
    void * get_void() {
       return self->data();
    }
    TYPE * get_data() {
       return self->data();
    }
};
%enddef
%vector_ext(char)
%vector_ext(int)
%vector_ext(float)
%vector_ext(double)

%extend std::vector<char> {
    void null_at(n_uint64_t i) {
      self->operator[](i)='\0';
    }
};

//%include "numpy.i" //included in hup.i
%include "std_iostream.i"
%include "file.i"

FILE *fopen(char *, char *);
int fclose(FILE *);
unsigned fread(void *ptr, unsigned size, unsigned nobj, FILE *);
unsigned fwrite(void *ptr, unsigned size, unsigned nobj, FILE *);
int feof(FILE *stream);

//since the limeEOM implementation is not found, just ignore it here
//we must ignore it before include lime_header.h
%ignore limeEOM;

%include "lime_defs.h"
%include "lime_utils.h"
%include "lime_fseeko.h"
%include "lime_header.h"
%include "lime_writer.h"
%include "lime_reader.h"

%include "clime_writer.h"
%include "clime_reader.h"
%include "clime_utils.h"

%typemap(out) n_uint64_t
{
  return PyLong_FromUnsignedLong($1);
}

%inline %{
 bool fok(FILE *s) {return s!=NULL;}
 FILE * get_stdout() {return stdout;}
 FILE * get_stdin() {return stdin;}
 FILE * get_stderr() {return stderr;}

 unsigned long long get_value(n_uint64_t i){ return static_cast<unsigned long long>(i); }
%}

%init %{
 //   import_array(); //for numpy
%}

#endif /* SWIGPYTHON */
//http://swig.org/Doc1.3/SWIGPlus.html#SWIGPlus_nn12
