/*
* ===========================================================================
*
*                            PUBLIC DOMAIN NOTICE                          
*               National Center for Biotechnology Information
*                                                                          
*  This software/database is a "United States Government Work" under the   
*  terms of the United States Copyright Act.  It was written as part of    
*  the author's official duties as a United States Government employee and 
*  thus cannot be copyrighted.  This software/database is freely available 
*  to the public for use. The National Library of Medicine and the U.S.    
*  Government have not placed any restriction on its use or reproduction.  
*                                                                          
*  Although all reasonable efforts have been taken to ensure the accuracy  
*  and reliability of the software and data, the NLM and the U.S.          
*  Government do not and cannot warrant the performance or results that    
*  may be obtained by using this software or data. The NLM and the U.S.    
*  Government disclaim all warranties, express or implied, including       
*  warranties of performance, merchantability or fitness for any particular
*  purpose.                                                                
*                                                                          
*  Please cite the author in any work or product based on this material.   
*
* ===========================================================================
*
*
*  FileName: CKitColors2.h
*  Author:   Douglas Hoffman
*
*  1/26/15 - loads the file kitcolors2.0.xml which replaces kitcolors.xml
*    The class CKitColors uses this class and CKitList to build
*    its data structures to be compatible to its earlier version that
*    used kitcolors.xml
*/
#ifndef __C_KIT_COLORS_2_H__
#define __C_KIT_COLORS_2_H__

#include "nwx/nwxXmlPersistCollections.h"

class CKitColorDye : public nwxXmlPersist
{
public:
  CKitColorDye() : nwxXmlPersist(true),  m_setDyeNames(wxT("Name"))
  {
    RegisterAll(true);
  }
  virtual ~CKitColorDye() {}
  const std::set<wxString> *GetDyes() const
  {
    return m_setDyeNames.GetSetPtr();
  }
  const wxString &GetColorName() const
  {
    return m_sColor;
  }
  const wxString &GetKey() const
  {
    return m_sColor;
  }
  const wxColour &GetColorAnalyzed() const
  {
    return m_ColorAnalyzed;
  }
  const wxColour &GetColorRaw() const
  {
    return m_ColorRaw;
  }
  const wxColour &GetColorLadder() const
  {
    return m_ColorLadder;
  }
protected:
  virtual void RegisterAll(bool = false)
  {
    RegisterWxString(wxT("Color"),&m_sColor);
    Register(wxT("Names"),&m_setDyeNames);
    RegisterWxColour(wxT("analyzed"),&m_ColorAnalyzed);
    RegisterWxColour(wxT("raw"),&m_ColorRaw);
    RegisterWxColour(wxT("ladder"),&m_ColorLadder);
  }
private:
  wxString m_sColor;
  wxColour m_ColorRaw;
  wxColour m_ColorAnalyzed;
  wxColour m_ColorLadder;
  nwxXmlPersistSetWxString m_setDyeNames;
};

class CKitColors2 : public nwxXmlPersist
{
  //  new for v2.7 - loads the file kitcolors2.0.xml
  //  and is used by CKitColors to build the structure
public:
  CKitColors2() :
      nwxXmlPersist(true)
  {
    RegisterAll(true);
    Load();
  }
  virtual ~CKitColors2()
  {
    m_io.Cleanup();
  }
  const CKitColorDye &GetColorByName(const wxString &s) const
  {
    map<wxString,CKitColorDye *>::const_iterator itr =
      m_mapKitColors.find(s);
    return *(itr->second);
  }
protected:
  virtual void RegisterAll(bool = false)
  {
    Register(wxT("Dye"),&m_io,&m_mapKitColors);
  }
private:
  bool Load();
  map<wxString,CKitColorDye *> m_mapKitColors;
  TnwxXmlIOPersistMap<wxString,CKitColorDye> m_io;
};

#endif
