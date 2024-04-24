#pragma once
#include "Singleton.ipp"
#include <sw/redis++/redis.h>

class RedisManager : public Singleton<RedisManager>
{
	friend class Singleton<RedisManager>;
public:
	RedisManager();
	sw::redis::Redis& GetRedis();
private:
	sw::redis::Redis redis_;
};