#ifndef _ADSERVER_
#define _ADSERVER_

#include <vo/vo.h>

using namespace std;


class DeliverChain {

public:
    DeliverChain();

protected:
    DeliverChain m_tNextChain;

public:
    virtual void doChain (DeliverVO delivery) = 0;
    void setDeliverChain(DeliverChain nextChain) {
	this.m_tNextChain = nextChain;
    }

protected:
    void sendNextChain (DeliveryChain delivery) {
	if (m_tNextChain != null){
            m_tNextChain.doChain(delivery);
	}
    }
}

#endif
