#ifndef _INDEXER_
#define _INDEXER_

#include <string>
#include <map>
#include <list>
#include <vo/vo.h>

using namespace std;

class index {
public:
    AdDao                 m_dAdDao;
    LineItemAdDao         m_dLineItemDao;
    AdGroupDao            m_dAdGroupDao;
    LineItemAdUnitDao     m_dLineItemAdUnitDao;
    LineItemDao           m_dLineItemDao;
    LineItemPackageDao    m_dLineItemPackageDao;
    LineItemScheduleDao   m_dLineItemScheduleDao;
    LineItemTagDao        m_dLineItemTagDao;
    AdUnitDao             m_dAdUnitDao;


public:
    index();
    void makeAllIndex();
    void makeHourAllIndex();
    void makeHourIndex();
    void makeIndex();
    void makeDeltaIndex(LineItem newLineItem, LineItem oldLineItem);
    
private:
    void makeContentIndex (map<string, LineItem> lineItemMap,
		    map<string, Ad>  adMap;
		    map<string, bool> lineitemStatusMap);
    void makeBitsetIndex (map<string, map<string, BitSet> indexMap,
		    map<string, string[]> adUnitLineItemArray);
    void makePartBitsetIndex (list<AdUnit> unitList,
		    list<StringBitsetMapEntity> mapList,
		    List<StringArrayEntity> arrayList);




}

#endif
