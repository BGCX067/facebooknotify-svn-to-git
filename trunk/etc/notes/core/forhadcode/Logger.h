// Logger Class
// Created : 1-20-2006 (Forhad Ahmed)
// 
// The Logger class provides centalized access to output in a program.
// It can be configured to either log to a file, to a stream , or both.
// The Logger's main function is write(string) which writes a given
// string to the proper logging location.  The logger also provides
// enter(string) and leave(string) to log whenever the program enters
// or leaves a function.  These 2 functions add a tab space to the input
// text so that when the logging runs, one can see the function call
// depths 

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
 

class Logger
{
public:
	Logger(void);
	~Logger(void);

	enum LogMode {toFile, toStream};


	// logger initialization methods... initializes protected file and stream
	// handles.  also 'getters' for these protected handles.

	bool		setFile(char * file);
	fstream	*	getFileHandle();
	bool		setStream(ostream * out);
	ostream *   getStreamHandle();
	void		setMode(LogMode mode); 
	int 		getMode();


	// option setting methods... nothing too important

	void flatOutput(bool flat);
	void callStack(bool callstack);
	void setLogLevel(int loglevel);



	// main public interface.  main method is write(string). all the other
	// ones sort of 'derive' from write(string). for example, error(string) 
	// is nothing more than  write(string) with the word 'error' prepended 
	// to string. similar with warning(string), enter(string)... etc.

	void write(string logText);
	void writeInline(string logText);
	void error(string errorText);
	void warning(string warningText);
	void enter(string logText);
	void leave(string logText);

	void incrementLevel(void);
	void decrementLevel(void);

protected:

	// these write_(string, int) method is the one that does the actual
	// stream IO. the public write(string) method calls the write_(string, int)
	// method.  so do all the other public methods.  whitespace(int), indent(string &),
	// and align(string &) are used for formatting

	void	write_(string logText, LogMode m);
	string	whitespace(int n);
	void    indent(string & text);
	void	align(string& text);



	// sensitive protected data members.  the actual file and stream the logger
	// writes to using the write_(string, int) method

	fstream 	fileHandle;
	ostream *	streamHandle;



	// option flags and variables

	LogMode		mode;
	bool		showFlat;
	bool		showCallStack;
	int			maxLevel;



	// call stack depth counter. incremented when enter(string) is called.
	// decremented when leave(string) is called

	int			currentLevel;

};

#endif
