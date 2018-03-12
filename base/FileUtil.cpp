#pragma once
#include "FileUtil.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <cstdio>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;


size_t AppendFile::write(const char* logline,size_t len)
{
	return fwrite_unlocked(logline,1,len,fp_);
}


AppendFile::AppendFile(string filename):
	fp_(fopen(filename.c_str(),"ae"))
{
	setbuffer(fp_,buffer_,sizeof buffer_);
}

AppendFile::~AppendFile()
{
	fclose(fp_);
}

void AppendFile::append(const char* logline,const size_t len)
{
	size_t n=this->write(logline,len);
	size_t remain=len-n;
	while(remain>0)
	{
		size_t res=this->write(logline+n,remain);
		if(res==0)
		{
			int err=ferror(fp_);
			if(err)fprintf(stderr,"AppendFile::append() failed\n");
			break;
		}
		n+=res;
		remain=len-n;
	}
}

void AppendFile::flush()
{
	fflush(fp_);
}