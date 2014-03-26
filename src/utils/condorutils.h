#ifndef CONDOR_UTILS_
#define CONDOR_UTILS_

#include <string>
#include <map>
using namespace std;

typedef map<string, map<string, string> > Config;
class ConfigParser {

  public:
    Config            conf_;

  public:
                      ConfigParser ();
    bool              Parse (const char * sFileName, const char * pBuffer = NULL);
    bool              ReParse (const char * sFileName, const char * pBuffer = NULL);

  protected:
    string            file_name_;
    int               line_;
    string            section_type_;
    string            section_name_;
    char              error_[ 1024 ];
    int               warnings_;
    static const int  WARNS_THRESH = 5;

  protected:
    bool              IsPlainSection (const char * sKey);
    bool              IsNamedSection (const char * sKey);
    bool              AddSection (const char * sType, const char * sSection);
    void              AddKey (const char * sKey, char * sValue);
    bool              ValidateKey (const char * sKey);
    char *            GetBufferString (char * szDest, int iMax, const char * szSource);

         	  
}


#endif
