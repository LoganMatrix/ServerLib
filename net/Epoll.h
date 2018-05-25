#pragma once
#include "Channel.h"
#include <vector>
#include <unordered_map>
#include <sys/epoll.h>
#include <memory>
using namespace std;
typedef shared_ptr<Channel> SP_Channel;
class Epoll
{
public:
	Epoll();
	~Epoll();
	void epoll_add(SP_Channel request,int timeout);
	void epoll_mod(SP_Channel request,int timeout);
	void epoll_del(SP_Channel request);
	std::vector<std::shared_ptr<Channel> > poll();
	std::vector<std::shared_ptr<Channel> > getEventsRequest(int events_num);
	int getEpollFd()
	{
		return epollFd_;
	}
	void handleExpired();
	
private:
	static const int MAXFDS = 100000;
	int epollFd_;
	std::vector<epoll_event> events_;
	std::shared_ptr<Channel> fd2chan_[MAXFDS];


};