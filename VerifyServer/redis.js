const Redis = require("ioredis");
const config = require("./config");

const redis = new Redis({
	host: config.redisHost,
	port: config.redisPort,
});

redis.on("error", function (error) {
	console.error("Redis connected error:", error);
	redis.quit();
});

async function get(key) {
	try {
		const result = await redis.get(key);
		if (result === null) {
			console.log("Redis get ", key, " failed!");
			return null;
		}
		console.log("Redis get ", key, " ", result);
		return result;
	} catch (error) {
		console.log("RedisGet error: ", error);
		return null;
	}
}

async function exists(key) {
	try {
		const result = await redis.exists(key);
		if (result === 0) {
			console.log("Redis ", key, " not exists!");
			return null;
		}
		console.log("Redis ", key, " exists!");
		return result;
	} catch (error) {
		console.log("RedisExists error: ", error);
		return null;
	}
}

async function SetExpire(key,value, expire){
    try{
        await redis.set(key,value)
        await redis.expire(key, expire);
        return true;
    }catch(error){
        console.log("RedisExpire error: ", error);
        return false;
    }
}

function quit(){
    redis.quit();
}

module.exports = { get, exists, SetExpire, quit };