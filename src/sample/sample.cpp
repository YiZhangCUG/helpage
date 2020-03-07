#include "../lib/helpage.h"

int main(int argc, char const *argv[])
{
	std::string ex_name = "Test Program";
	std::string ex_usage = ex_name;
	ex_usage += " [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c] [-a] [-b] [-c]";
	// 声明一个帮助信息类
	DispHelp dh;
	// 设定左右空白大小
	dh.ChangeLayerOut(5,10);
	// 添加头信息
	dh.AddHeadInfo(ex_name,"1.0","some information about your program. some information about your program. \
		some information about your program. some information about your program. some information about your program.",
		"Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. \
		Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it. Who wrote it.");
	dh.AddUsage(ex_usage);
	dh.AddUsage(ex_usage);
	dh.AddOption("first option. bala bala bala...","-a","--add=<number>");
	dh.AddOptionSec("1. xxxxxxxxxxx");
	dh.AddOption("second option. this very long. this very long. this very long. this very long. this very long. this very long. this very long. \
		 this very long. this very long. this very long. this very long.","","--only-long");
	dh.AddOption("third option","-c");
	dh.AddOptionSec("2. jjjjjjjjjjj",0);
	dh.AddOptionSec("cscscscscsc",1);
	dh.AddExample("test -a sdsd -b sdsdtest -a sdsd -b sdsdtest -a sdsd -b sdsdtest -a sdsd -b sdsdtest -a sdsd -b sdsdtest -a sdsd -b sdsdtest -a sdsd -b sdsd");
	dh.Show();

	// 设定左右空白
	//std::cerr << std::endl << std::endl;
	//dh.ChangeLayerOut(5,5);
	//dh.Show();
	return 0;
}