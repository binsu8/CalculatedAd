#ifndef _ADSERVER_
#define _ADSERVER_

#include <vo/vo.h>

using namespace std;


class Filter : public DeliverChain {

public:
    Filter();
    virtual ~Filter();

}

#endif
