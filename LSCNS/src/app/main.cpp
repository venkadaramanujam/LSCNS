
#include <iostream>
#include "../includes/wch.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Watcher w;
	cout<<w.init((char *)"../../shared/", NULL)<<endl;
	w.watch();
	return 0;
}
