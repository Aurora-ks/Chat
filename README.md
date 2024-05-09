# 概述
> 此版只是实现基本的通信功能，许多地方在设计实现上有所缺陷，有待后续优化

本项目使用qt构建客户端，使用asio、beast、grpc实现多服务端，服务之间使用rpc通信。实现了基本的登录、注册、聊天的功能。
# 服务端设计
![](https://cdn.nlark.com/yuque/0/2024/jpeg/43019167/1714720323512-64ebf9bd-7744-4f5d-a0c2-44a2c08fdbef.jpeg)
# 客户端设计

- 登录界面

![image.png](https://cdn.nlark.com/yuque/0/2024/png/43019167/1714717604103-c2474843-7561-48d8-b171-c1e64d43f156.png#averageHue=%23efeeee&clientId=u1e92726f-456b-4&from=paste&height=304&id=uf80effdd&originHeight=456&originWidth=606&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=10409&status=done&style=none&taskId=uae561855-1931-4ca5-876e-808eb410d3d&title=&width=404)

- 注册界面

![image.png](https://cdn.nlark.com/yuque/0/2024/png/43019167/1714717637719-174a431b-d4ff-4c2e-9f83-01747c7d0340.png#averageHue=%23eeeeed&clientId=u1e92726f-456b-4&from=paste&height=447&id=ue36a789b&originHeight=670&originWidth=466&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=16041&status=done&style=none&taskId=u69f39241-1574-493f-8ff8-ffeb41b4eb1&title=&width=310.6666666666667)

- 主界面

![image.png](https://cdn.nlark.com/yuque/0/2024/png/43019167/1714717730471-f9470161-48ab-4174-8e6a-835d5eca803f.png#averageHue=%23f9f9f8&clientId=u1e92726f-456b-4&from=paste&height=623&id=u6d3da3e3&originHeight=1014&originWidth=609&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=99469&status=done&style=none&taskId=u21f96e5c-b265-4c7c-a7c2-8d10cd5c249&title=&width=374)

- 聊天界面

![image.png](https://cdn.nlark.com/yuque/0/2024/png/43019167/1714717797901-6477dad9-13c5-473a-87c5-7248b54dc293.png#averageHue=%23fbfbfb&clientId=u1e92726f-456b-4&from=paste&height=587&id=u3cecbfd3&originHeight=1005&originWidth=1122&originalType=binary&ratio=1.5&rotation=0&showTitle=false&size=70954&status=done&style=none&taskId=uf4128f52-a3ec-43fa-8b89-a113797bca1&title=&width=655.6666870117188)
# 使用

- Windows
   - 安装Redis
   - 启动Redis服务
   - 安装node.js
   - 在VerifyServer目录下执行命令
   ```powershell
   npm install
   npm run server
   ```

   - 安装Mysql
   - 确保账户名为root，密码为123456，在项目根目录下使用cmd执行命令`mysql -uroot -p123456 <mysql.sql`

   - 进入build-win_x64目录依次启动服务
# 开发环境

- qt 6.6.1
- Visual Studio 2022
- boost 1.84.0
- grpc 1.34.0
- jsoncpp 1.9.5
- redis-plus-plus:x64-windows 1.3.10
- mysql-connector-c++-8.3.0-winx64

[详细介绍](https://www.yuque.com/aurora-1emum/dq3xbm/ag12arwae0oysdly)