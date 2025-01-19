//directors="1"
%module (docstring="XPathReader C++ wrapper in Python, May. 2025, Shun Xu <xushun@sccas.cn>") xpathreader
%{

#include "xpath_reader.h"
#include "xml_writer.h"
#include "xml_struct_writer.h"
#include "xml_array_writer.h"
#include "xml_simpleschemawriter.h"
#include "xml_document.h"
#include "xml_attribute.h"

using namespace XMLStructWriterAPI;
using namespace XMLWriterAPI;

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
%include "std_string.i"

//%include "numpy.i" //included in hup.i
%include "std_iostream.i"
%include "file.i"

FILE *fopen(char *, char *);
int fclose(FILE *);
unsigned fread(void *ptr, unsigned size, unsigned nobj, FILE *);
unsigned fwrite(void *ptr, unsigned size, unsigned nobj, FILE *);
int feof(FILE *stream);

%ignore XMLWriterAPI::XMLWriterBase; //abstract methods

%include "xml_array.h"
%include "xml_tcomplex.h"
%include "xml_struct_writer.h"
%include "xml_array_writer.h"
%include "xml_simpleschemawriter.h"
%include "xml_document.h"
%include "xml_attribute.h"
%include "xpath_reader.h"
%include "xml_writer.h"

%extend XMLXPathReader::XPathReader {
  %template(getXPathInt)    getXPath<int>;
  %template(getXPathFloat) getXPath<float>;
  %template(getXPathDouble) getXPath<double>;
  %template(getXPathString) getXPath<std::string>;
  
};

%inline %{
 bool fok(FILE *s) {return s!=NULL;}
 FILE * get_stdout() {return stdout;}
 FILE * get_stdin() {return stdin;}
 FILE * get_stderr() {return stderr;}
%}

#endif /* SWIGPYTHON */
//http://swig.org/Doc1.3/SWIGPlus.html#SWIGPlus_nn12
