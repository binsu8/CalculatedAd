#ifndef _VO_
#define _VO_

#include <vo/vo.h>
#include <string>
#include <map>
#include <list>

using namespace std;


class DeliverVO {

public:
    DeliverChain();

public:
    string[]                      m_sAdUnit;
    int                           m_iRotate;
    int                           m_iHour;

    string                        m_sIp;
    string                        m_sZone;
    string                        m_sUserId;
    string                        m_sCookied;
    string                        m_sReferralUrl;
    string                        m_UniqueHashcode;
    string                        m_sChannel;
    string                        m_sTimeStamp;
    string                        m_sReponseString;

    map<string, int>              m_mAdNumberMap;
    map<string, int>              m_mRotateMap;
    map<string, string>           m_mRequestMap;
    map<string, bool>             m_mAdvertiseUniqueMap;
    map<string, list<TagEntity>>  m_mUserQueryData;
    map<string, list<TagEntity>>  m_mUserQueryDataMap;
    map<string, AdUnitVO>         m_mAdUnitInfoMap;
    map<string, DeliverAd>        m_mDeliverAd;
    map<string, TargetingTypeSearchTree>         m_mSearchTreeMap;


}

#endif
