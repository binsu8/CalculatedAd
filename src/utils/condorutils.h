//
// $Id$
//

//
// Copyright (c) 2001-2011, Andrew Aksyonoff
// Copyright (c) 2008-2011, Sphinx Technologies Inc
// All rights reserved
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License. You should have
// received a copy of the GPL license along with this program; if you
// did not, you can find it at http://www.gnu.org/
//

/// @file sphinxutils.h
/// Declarations for the stuff shared by all Sphinx utilities.

#ifndef _CONDOR_UTILS_
#define _CONDOR_UTILS_

#include <string>
#include <map>
using namespace std;

typedef map< string, map<string, string> > Config;
class ConfigParser {

public:
    Config            m_tConf;

public:
                      ConfigParser ();
    bool              parse (const char * sFileName, const char * pBuffer = NULL);
    bool              reParse (const char * sFileName, const char * pBuffer = NULL);

protected:
    string            m_sFileName;
    int               m_iLine;
    string            m_sSectionType;
    string            m_sSectionName;
    char              m_sError [ 1024 ];
    int               m_iWarnings;
    static const int  WARNS_THRESH = 5;

protected:
    bool              isPlainSection (const char * sKey);
    bool              isNamedSection (const char * sKey);
    bool              addSection (const char * sType, const char * sSection);
    void              addKey (const char * sKey, char * sValue);
    bool              validateKey (const char * sKey);
    char *            getBufferString (char * szDest, int iMax, const char * szSource);

         	  
}


#endif
