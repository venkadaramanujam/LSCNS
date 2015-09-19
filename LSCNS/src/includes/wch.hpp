
#ifndef WCH_HPP
#define WCH_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "err.hpp"
#include "evhandler.hpp"

using namespace std;

class Watcher
{
	private:
		int fd;
		int wd;
		EventRecv *ev;

	public:
		int init(char *dirpath, EventRecv *ev);
		int watch();
		int stop();
};

#endif
