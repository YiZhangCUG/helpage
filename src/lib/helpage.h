#ifndef _GCTL_DISPLAYHELP_H
#define _GCTL_DISPLAYHELP_H
#include "string"
#include "unistd.h"
#include "sys/ioctl.h"
#include "sstream"
#include "iostream"
#include "vector"

namespace gctl
{
	class DispHelp
	{
	public:
		DispHelp();
		/**
		 * @brief      添加程序头信息
		 *
		 * @param[in]  s1      程序名称
		 * @param[in]  s2   程序的版本
		 * @param[in]  s3  程序的简要描述
		 * @param[in]  s4    程序的作者信息
		 */
		void AddHeadInfo(std::string s1,std::string s2,std::string s3,std::string s4);
		/**
		 * @brief      添加程序用法
		 *
		 * @param[in]  usg  程序用法
		 */
		void AddUsage(std::string usg);
		/**
		 * @brief      添加控制符信息
		 *
		 * @param[in]  msg  控制符说明
		 * @param[in]  sflag   短控制符号
		 * @param[in]  lflag   长控制符号，默认为空
		 */
		void AddOption(std::string msg,std::string sflag,std::string lflag = "");
		/**
		 * @brief      添加二级控制符号说明
		 *
		 * @param[in]  msg  控制说明
		 * @param[in]  index       一级控制符号的索引，默认为-1，即最末端的一级符号
		 */
		void AddOptionSec(std::string msg,int index = -1);
		/**
		 * @brief      添加一个例子
		 *
		 * @param[in]  ex    例子字符串
		 */
		void AddExample(std::string ex);
		/**
		 * @brief      调整版面布局
		 *
		 * @param[in]  left   左侧空白字符数
		 * @param[in]  right  右侧空白字符数
		 */
		void ChangeLayerOut(int left,int right);
		/**
		 * @brief      显示帮助信息
		 */
		void Show();
	private:
		/**
		 * @brief      选项类型 这是DispHelp这个类专用的 定义为类的私有类型
		 */
		struct option
		{
			std::string flag_s,flag_l;
			std::string message;
			std::vector<std::string> sec_message;
			option();
		};
		std::vector<option> options;

		std::string ex_name,version,descript,author;
		int front_space,back_space;
		std::vector<std::string> examples;
		std::vector<std::string> usages;
	};
}
#endif //_GCTL_DISPLAYHELP_H