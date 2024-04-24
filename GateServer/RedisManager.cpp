#include "RedisManager.h"

using namespace sw::redis;
using namespace std;

static ConnectionOptions option()
{
	//TODO: 使用配置文件读取设置
	ConnectionOptions options;
	options.host = "127.0.0.1";
	options.port = 6379;
	return options;
}

static ConnectionPoolOptions PoolOption()
{
	//TODO: 使用配置文件读取设置
	ConnectionPoolOptions PoolOptions;
	PoolOptions.size = 3;
	return PoolOptions;
}

RedisManager::RedisManager()
	:redis_(option(), PoolOption())
{}

Redis& RedisManager::GetRedis()
{
	return redis_;
}