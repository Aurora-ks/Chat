create database chat;
use chat;

/*
 Navicat Premium Data Transfer

 Source Server         : db
 Source Server Type    : MySQL
 Source Server Version : 80034 (8.0.34)
 Source Host           : localhost:3306
 Source Schema         : chat

 Target Server Type    : MySQL
 Target Server Version : 80034 (8.0.34)
 File Encoding         : 65001
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `uid` int NOT NULL AUTO_INCREMENT,
  `user_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `email` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`uid`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

/*
 Navicat Premium Data Transfer

 Source Server         : db
 Source Server Type    : MySQL
 Source Server Version : 80034 (8.0.34)
 Source Host           : localhost:3306
 Source Schema         : chat

 Target Server Type    : MySQL
 Target Server Version : 80034 (8.0.34)
 File Encoding         : 65001
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for friend
-- ----------------------------
DROP TABLE IF EXISTS `friend`;
CREATE TABLE `friend`  (
  `user_id` int NOT NULL,
  `friend_id` int NOT NULL,
  PRIMARY KEY (`user_id`, `friend_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;

CREATE DEFINER=`root`@`localhost` PROCEDURE `UserRegister`(IN `new_name` varchar(255),IN `new_password` varchar(255),IN `new_email` varchar(255),OUT `result` int)
BEGIN
	-- 如果在执行过程中遇到任何错误，则回滚事务
    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        -- 回滚事务
        ROLLBACK;
        -- 设置返回值为-1，表示错误
        SET result = -1;
    END;

    -- 开始事务
    START TRANSACTION;

		-- 检查用户名是否已存在
    IF EXISTS (SELECT 1 FROM `user` WHERE `user_name` = new_name) THEN
        SET result = 0; -- 用户名已存在
        COMMIT;
    ELSE
        -- 用户名不存在，检查email是否已存在
        IF EXISTS (SELECT 1 FROM `user` WHERE `email` = new_email) THEN
            SET result = 0; -- email已存在
            COMMIT;
        ELSE
            -- 在user表中插入新记录
            INSERT INTO `user` (`user_name`, `email`, `password`) VALUES (new_name, new_email, new_password);
            -- 设置result为新插入的uid
						SELECT `uid` INTO @new_id FROM `user` WHERE `user_name` = new_name;
            SET result = @new_id; -- 插入成功，返回新的uid
            COMMIT;

        END IF;
    END IF;
END

CREATE DEFINER=`root`@`localhost` PROCEDURE `GetFriend`(IN `id` int)
BEGIN
	SELECT uid, user_name
	FROM
	(
	SELECT `user_id` AS uid
	FROM `friend`
	WHERE `friend_id` = id
	UNION
	SELECT `friend_id` AS uid
	FROM `friend`
	WHERE `user_id` = id
	) as f NATURAL JOIN `user`;

END

CREATE DEFINER=`root`@`localhost` PROCEDURE `AddFriend`(IN `friend_name` varchar(255),IN `user_id` int,OUT `result` int)
BEGIN
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
				ROLLBACK;
        -- 好友关系已存在
        SET result = -3;
    END;

	START TRANSACTION;

	-- 判断用户是否存在
	SELECT `uid` INTO @uid
	FROM `user`
	WHERE `user_name` = friend_name;

	IF @uid IS NULL THEN
		SET result = -2;
		COMMIT;
	ELSE
	  -- 确保user_id小于uid，如果大于则交换数值
		IF user_id > @uid THEN
			SET user_id = @uid;
			SET @uid = @original_user_id := user_id; -- 交换数值
		END IF;
		-- 插入好友关系
		INSERT INTO friend(user_id, friend_id)
		VALUES(user_id, @uid);
		SET result = @uid;
		COMMIT;
	END IF;
END