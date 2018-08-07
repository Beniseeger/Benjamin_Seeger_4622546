#include "stdafx.h"
#include "ConsoleUtils.h"

#include "stdafx.h"
#include <ioStream>
#include <string>
#include <ctime>

using std::cin;
using std::string;
using std::cout;

int ConsoleUtils::readInteger()
{
	int result = -1;
	cin >> result;
	if (cin.fail())
	{
		cin.clear();
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return result;
}

long ConsoleUtils::readLong()
{
	long result = -1;
	cin >> result;
	if (cin.fail())
	{
		cin.clear();
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return result;
}

double ConsoleUtils::readDouble()
{
	double result = -1;
	cin >> result;
	if (cin.fail())
	{
		cin.clear();
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return result;
}

std::string ConsoleUtils::readString()
{
	string line;
	cin >> line;
	if (cin.fail())
	{
		cin.clear();
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return line;
}

time_t ConsoleUtils::readTime()
{
	time_t t;
	struct tm ts;

	ts.tm_sec = 0;      /* Sekunden */
	ts.tm_min = 0;     /* Minuten */
	ts.tm_hour = 0;     /* Stunden */
	ts.tm_mday = readSaveInteger("Tag(0-30): ");     /* Tag im Monat  */
	ts.tm_mon = readSaveInteger("\nMonat(0-11): ");      /* Monat - 1*/
	ts.tm_year = readSaveInteger("\nJahr: ");;     /* Jahr - 1900 */
	ts.tm_wday = readSaveInteger("\Wochentag(0-6): ");;      /* Wochentag  */

	t = mktime(&ts);
	return t;
}

int ConsoleUtils::readSaveInteger(std::string message)
{
	int result = -1;
	while (result == -1)
	{
		cout << message;
		result = readInteger();
	}
	return result;
}
