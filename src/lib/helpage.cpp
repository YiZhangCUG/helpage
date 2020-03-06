#include "helpage.h"

gctl::DispHelp::DispHelp()
{
	front_space = 0;
	back_space = 10;
	ex_name = "Execuable";
	version = "0.0.1";
	descript = "Brief information about this command.";
	author = "Author's information.";
}

gctl::DispHelp::option::option()
{
	flag_s = flag_l = message = "";
}

void gctl::DispHelp::AddHeadInfo(std::string s1,std::string s2,std::string s3,std::string s4)
{
	ex_name = s1; version = s2; descript = s3; author = s4;
	return;
}

void gctl::DispHelp::AddUsage(std::string usg)
{
	usages.push_back(usg);
	return;
}

void gctl::DispHelp::AddOption(std::string msg,std::string sflag,std::string lflag)
{
	option tmp_option;
	tmp_option.message = msg; tmp_option.flag_s = sflag; tmp_option.flag_l = lflag;
	options.push_back(tmp_option);
	return;
}

void gctl::DispHelp::AddOptionSec(std::string msg,int index)
{
	if (index < 0)
	{
		options.back().sec_message.push_back(msg);
	}
	else options[index].sec_message.push_back(msg);
	return;
}

void gctl::DispHelp::AddExample(std::string ex)
{
	examples.push_back(ex);
	return;
}

void gctl::DispHelp::ChangeLayerOut(int left,int right)
{
	front_space = left; back_space = right;
	return;
}

void gctl::DispHelp::Show()
{
	int line_length;
	std::string segment,full_message;
	std::stringstream ss_message;
	//获取终端窗口的行列数
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	//显示头信息
	full_message = ex_name + " " + version + " - " + descript;
	ss_message.clear(); ss_message.str(full_message);

	line_length = front_space + back_space;
	while(ss_message >> segment)
	{
		if ((line_length+segment.length()+1) <= w.ws_col)
		{
			if (line_length == (front_space + back_space))
			{
				for (int i = 0; i < front_space; i++)
					std::cerr << " ";
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
			else
			{
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < front_space+8; i++)
				std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+9+front_space+back_space);
		}
	}
	std::cerr << std::endl;
	for (int i = 0; i < front_space; i++)
		std::cerr << " ";
	std::cerr << "=*==*====*====*==*=" << std::endl;

	ss_message.clear(); ss_message.str(author);
	line_length = front_space + back_space;;
	while(ss_message >> segment)
	{
		if ((line_length+segment.length()+1) <= w.ws_col)
		{
			if (line_length == (front_space + back_space))
			{
				for (int i = 0; i < front_space; i++) std::cerr << " ";
				std::cerr << "Author: " << segment << " ";
				line_length += (segment.length()+9);
			}
			else
			{
				std::cerr << segment << " ";
				line_length += (segment.length()+1);
			}
		}
		else
		{
			std::cerr << std::endl;
			for (int i = 0; i < front_space+8; i++) std::cerr << " ";
			std::cerr << segment << " ";
			line_length = (segment.length()+9+front_space+back_space);
		}
	}
	std::cerr << std::endl << std::endl;

	if (!usages.empty())
	{
		for (int i = 0; i < usages.size(); i++)
		{
			ss_message.clear(); ss_message.str(usages[i]);

			line_length = front_space + back_space + 4;
			while(ss_message >> segment)
			{
				if ((line_length+segment.length()+1) <= w.ws_col)
				{
					if (line_length == (front_space+back_space+4))
					{
						for (int j = 0; j < front_space; j++) std::cerr << " ";
						if (usages.size() > 1)
						{
							std::cerr << "Usage" << i+1 << ": " << segment << " ";
						}
						else std::cerr << "Usage:  " << segment << " ";
						line_length += (segment.length()+1);
					}
					else
					{
						std::cerr << segment << " ";
						line_length += (segment.length()+1);
					}
				}
				else
				{
					std::cerr << std::endl;
					for (int j = 0; j < front_space+8; j++) std::cerr << " ";
					std::cerr << segment << " ";
					line_length = (segment.length()+10+front_space+back_space);
				}
			}
			std::cerr << std::endl << std::endl;
		}
	}

	if (!options.empty())
	{
		//找到最长的选项作为排版的依据
		int temp_len, remain_len, max_opt_length = -1;
		for (int i = 0; i < options.size(); i++)
		{
			temp_len = options[i].flag_s.length() + options[i].flag_l.length();
			max_opt_length = std::max(max_opt_length, temp_len);
		}

		for (int i = 0; i < front_space; i++)
			std::cerr << " ";
		std::cerr << "Options:" << std::endl;

		for (int i = 0; i < options.size(); i++)
		{
			for (int j = 0; j < front_space+2; j++)
				std::cerr << " ";

			temp_len = options[i].flag_s.length() + options[i].flag_l.length();
			remain_len = max_opt_length - temp_len;
			std::cerr << options[i].flag_s << "    " << options[i].flag_l << "    ";
			for (int j = 0; j < remain_len; j++)
				std::cerr << " ";

			ss_message.clear(); ss_message.str(options[i].message);
			line_length = front_space + back_space + max_opt_length + 11;
			while(ss_message >> segment)
			{
				if ((line_length+segment.length()+1) <= w.ws_col)
				{
					std::cerr << segment << " ";
					line_length += (segment.length()+1);
				}
				else
				{
					std::cerr << std::endl;
					for (int j = 0; j < front_space+max_opt_length+10; j++)
						std::cerr << " ";
					std::cerr << segment << " ";
					line_length = (segment.length()+10+max_opt_length+front_space+back_space);
				}
			}
			std::cerr << std::endl;

			if (!options[i].sec_message.empty())
			{
				for (int j = 0; j < options[i].sec_message.size(); j++)
				{
					for (int k = 0; k < front_space+max_opt_length+10; k++)
						std::cerr << " ";

					ss_message.clear(); ss_message.str(options[i].sec_message[j]);
					line_length = front_space + back_space + max_opt_length + 11;
					while(ss_message >> segment)
					{
						if ((line_length+segment.length()+1) <= w.ws_col)
						{
							std::cerr << segment << " ";
							line_length += (segment.length()+1);
						}
						else
						{
							std::cerr << std::endl;
							for (int k = 0; k < front_space+max_opt_length+10; k++)
								std::cerr << " ";
							std::cerr << segment << " ";
							line_length = (segment.length()+10+max_opt_length+front_space+back_space);
						}
					}
					std::cerr << std::endl;
				}
			}
		}
		std::cerr << std::endl;
	}

	if (!examples.empty())
	{
		for (int i = 0; i < front_space; i++) std::cerr << " ";
		std::cerr << "Examples:" << std::endl;
		for (int i = 0; i < examples.size(); i++)
		{
			ss_message.clear(); ss_message.str(examples[i]);

			line_length = front_space + back_space + 8;
			while(ss_message >> segment)
			{
				if ((line_length+segment.length()+1) <= w.ws_col)
				{
					if (line_length == (front_space+back_space+8))
					{
						for (int i = 0; i < front_space+8; i++) std::cerr << " ";
						std::cerr << segment << " ";
						line_length += (segment.length()+1);
					}
					else
					{
						std::cerr << segment << " ";
						line_length += (segment.length()+1);
					}
				}
				else
				{
					std::cerr << std::endl;
					for (int i = 0; i < front_space+8; i++) std::cerr << " ";
					std::cerr << segment << " ";
					line_length = (segment.length()+10+front_space+back_space);
				}
			}
			std::cerr << std::endl;
		}
		std::cerr << std::endl;
	}
	return;
}