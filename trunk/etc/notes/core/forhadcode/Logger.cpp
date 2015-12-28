#include "Logger.h"

Logger::Logger(void)
{
	this->streamHandle = &cout;
	this->mode = Logger::toStream;
	this->currentLevel = 0;

	this->showFlat = false;
	this->mode = toFile;
	this->setFile("log.txt");



}


void Logger::incrementLevel(void)
{
	this->currentLevel++;
}

void Logger::decrementLevel(void)
{
	this->currentLevel--;
}

Logger::~Logger(void)
{
	this->fileHandle.close();
}

bool Logger::setFile(char * file)
{
	this->fileHandle.open(file,  ios::out);
	return this->fileHandle.is_open();
}

fstream	*	Logger::getFileHandle()
{
	return &fileHandle;
}


bool Logger::setStream(ostream * out)
{
	this->streamHandle = out;
	return true;
}

ostream	*	Logger::getStreamHandle()
{
	return this->streamHandle;
}


void Logger::setMode(LogMode mode) 
{
	this->mode = mode;
}

int Logger::getMode()
{
	return this->mode;
}

void Logger::flatOutput(bool flat)
{
	this->showFlat = flat;
}


void Logger::callStack(bool callstack)
{
	this->showCallStack = callstack;
}

void Logger::setLogLevel(int loglevel)
{
	this->maxLevel = loglevel;
}

void Logger::write(string logText )
{

	indent(logText);
	align(logText);

	this->write_(logText+"\n\n", this->mode);

}

void Logger::writeInline(string logText)
{	
	indent(logText);
	align(logText);

	this->write_(logText, this->mode);

}

void Logger::error(string errorText)
{
	errorText = "ERROR: " + errorText;

	indent(errorText);
	align(errorText);

	this->write_(errorText+"\n\n", this->mode);

}

void Logger::warning(string warningText)
{
	warningText = "WARNING: " + warningText;

	indent(warningText);
	align(warningText);

	this->write_(warningText+"\n\n", this->mode);
}

void Logger::enter(string logText )
{
	

		logText = "ENTER> " + logText;
		
		indent(logText);
		align(logText);

		if(this->showCallStack) this->write_(logText+"\n\n", this->mode);
		this->currentLevel++;



}
void Logger::leave(string logText)
{

	logText = "<LEAVE " + logText;


	if(this->currentLevel > 0)
	{
		this->currentLevel--;

		indent(logText);
		align(logText);
		if(this->showCallStack) this->write_(logText+"\n\n", this->mode);
	
	}
	else
	{
		if(this->showCallStack) this->write_("- negative function call depth (mismatched enter/leave?)\n\n", this->mode);
	}
}

void Logger::write_(string logText, LogMode m)
{
	if(this->mode == Logger::toFile)
	{
		if(this->fileHandle.is_open());
		{
			this->fileHandle.write(logText.c_str(), logText.length());
		}
	}
	else if(this->mode == Logger::toStream)
	{
		if(this->streamHandle != 0)
		{
			this->streamHandle->write(logText.c_str(), logText.length());
		}
	}
	else
	{
		if(this->fileHandle.is_open());
		{
			this->fileHandle.write(logText.c_str(), logText.length());
		}
	}

}


string Logger::whitespace(int n)
{
	string ws = "";
	for(int c = 0; c < n; c++)
	{
		ws.append(" ");
	}
	
	return ws;
}

void Logger::align(string & s)
{
	if(!this->showFlat)
	{
		for(int c = 0 ; c < s.length(); c++)
		{
			if(s[c] == '\n')
			{
				string padding = whitespace(currentLevel*5);
				s.insert(c+1,padding);
				c+=padding.length();
			}
		}
	}
}

void Logger::indent(string & s)
{
	
	if(!this->showFlat)
	{
		s=whitespace(currentLevel*5)+s;
	}
}
