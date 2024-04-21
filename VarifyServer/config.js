const fs = require('fs');

const config = JSON.parse(fs.readFileSync('./config.json', 'utf8'));

const serverHost = config.server.host;
const serverPort = config.server.port;
const varifyHost = config.varify.host;
const varifyPort = config.varify.port;
const varifyEmail = config.email.user;
const varifyPassword = config.email.password;
const redisHost = config.redis.host;
const redisPort = config.redis.port;

module.exports = { serverHost, serverPort, varifyHost, varifyPort, varifyEmail, varifyPassword, redisHost, redisPort };