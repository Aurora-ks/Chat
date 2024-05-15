const fs = require('fs');

const config = JSON.parse(fs.readFileSync('./config.json', 'utf8'));

const serverHost = config.server.host;
const serverPort = config.server.port;
const verifyHost = config.verify.host;
const verifyPort = config.verify.port;
const verifyEmail = config.email.user;
const verifyPassword = config.email.password;
const redisHost = config.redis.host;
const redisPort = config.redis.port;

module.exports = { serverHost, serverPort, verifyHost, verifyPort, verifyEmail, verifyPassword, redisHost, redisPort };