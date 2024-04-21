const grpc = require("@grpc/grpc-js");
const message_proto = require("./proto");
const emailModule = require("./email");
const Errors = require("./ErrorCodes");
const config = require("./config");
const redis = require("./redis");

function generateRandomNumber() {
	let randomNumber = 0;
	const multiplier = 100000; // 10^5, 用于生成5位数

	// 生成5位随机数
	while (randomNumber < 10000) {
		randomNumber = Math.floor(Math.random() * multiplier);
	}

	return randomNumber;
}

async function GetVarifyCode(call, callback) {
	console.log("email is ", call.request.email);
	try {
		let code = await redis.get(call.request.email);
		if(query === null){
			code = generateRandomNumber();
			let res = await redis.SetExpire(call.request.email, code, 180);
			if(!res){
				callback(null, { email: call.request.email, error: Errors.RedisErr });
				return;
			}
		}
		console.log("code is ", code);
		let text_str = "您的验证码为" + code + "请三分钟内完成注册";
		//发送邮件
		let mailOptions = {
			from: config.varifyEmail,
			to: call.request.email,
			subject: "验证码",
			text: text_str,
		};

		let send_res = await emailModule(mailOptions);
		console.log("send res is ", send_res);

		callback(null, { email: call.request.email, error: Errors.Success });
	} catch (error) {
		console.log("catch error is ", error);

		callback(null, { email: call.request.email, error: Errors.Exception });
	}
}

let server = new grpc.Server();
server.addService(message_proto.Varify.service, { GetVarifyCode: GetVarifyCode });
const host = config.serverHost+':'+config.serverPort;
server.bindAsync(host, grpc.ServerCredentials.createInsecure(), () => {
	console.log("varify server started on ", host);
});
