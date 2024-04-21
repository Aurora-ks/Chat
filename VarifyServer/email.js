const nodemailer = require("nodemailer");
const config = require("./config");

const transporter = nodemailer.createTransport({
	host: config.varifyHost,
	port: config.varifyPort,
	secure: true, // Use `true` for port 465, `false` for all other ports
	auth: {
		user: config.varifyEmail,
		pass: config.varifyPassword,
	},
});

function SendMail(mailOptions_) {
	return new Promise(function (resolve, reject) {
		transporter.sendMail(mailOptions_, function (error, info) {
			if (error) {
				console.log(error);
				reject(error);
			} else {
				console.log("邮件成功发送：" + info.response);
				resolve(info.response);
			}
		});
	});
}

module.exports = SendMail;