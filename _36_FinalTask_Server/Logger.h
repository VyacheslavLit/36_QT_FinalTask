#pragma once
#include <fstream>
#include <shared_mutex>
#include <thread>


class Logger
{
	std::shared_mutex m;
	fstream fs;
public:
	Logger()
	{
	}
	~Logger()
	{
	}
	void setLog(string log)
	{
		m.lock();
		fs.open("Logger.txt", ios::app);
		fs << log << endl;
		fs.close();
		m.unlock();
	}
	string getLog()
	{
		m.lock_shared();
		fs.open("Logger.txt", ios::in);
		string log1, log2, log3;
		while (fs)
		{
			log1 = log2;
			log2 = log3;
			getline(fs, log3);
		}
		fs.close();
		m.unlock_shared();
		return (log1 + "\n" + log2 + "\n" + log3);
	}
};
