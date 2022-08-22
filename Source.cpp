#include <iostream>
#include <ctime>                    // for the getTime function
#include <string>                   //for to_string()
//#include <format>                 // enable this for Option 2 in the formatTime12 function
#pragma warning(disable : 4996)     // stops a warning/error from localtime() where it would prefer localtime_s() feel free to ask me any questions.

//using namespace std;              // I commented this out for my own learning experience. I just want to learn what belongs in the std library.





/**
 * This function is based on the example at the bottom of this page: https://www.softwaretestinghelp.com/date-and-time-in-cpp/.
 * I can't figure out how to reference code, please correct me if needed.
 * 
 * \param hhmmss - tells the function which value I need
 * \return - hour, minute, or second
 */
int getTime(int hhmmss) {
	time_t ttime = time(0);
	tm* local_time = localtime(&ttime);

	switch (hhmmss) {
		case(0): {
			auto hour = 1 + local_time->tm_hour;
			return hour;
		}
		case(1): {
			auto min = 1 + local_time->tm_min;
			return min;
		}
		case(3): {
			auto sec = 1 + local_time->tm_sec;
			return sec;
		}
	}
}


/**
 *  formats single numbers as two digits
 * 
 * \return - int as two digits {01, 02, 03, ..., 11, 12}
 */
std::string twoDigitString(unsigned int n) {
	std::string twoNumbers;
	if (n < 10) {
		twoNumbers.append(std::to_string(0));          // I later learned about `sprintf_s()` which, (if I did it again) is what I would like to use, seems a little easier to read.
	}
	twoNumbers.append(std::to_string(n));
	return twoNumbers;
}

/**
 * repeats the `*` to use in formatting and organizing program output
 * 
 * \param size_t n = how many chars to return
 * \param char c - default is '*', can be anything if second param is another char
 * \return string of `*`
 */
std::string nCharString(size_t n, char c = '*') {
	std::string charString(n, c);                      // creates repeating characters (c) n number of times.
	return charString;
}

/**
 * Formats the time in military format
 *
 * \param h, hours 0 to 23
 * \param m, minutes 0 to 59
 * \param s, seconds 0 to 59
 *
 * \return hh:mm:ss
 */
std::string formatTime24(unsigned int h, unsigned int m, unsigned int s) {

	std::string time24;
	
	time24.append(twoDigitString(h) + ":");            // could have been done on one .append() but chose to do three for readability
	time24.append(twoDigitString(m) + ":");
	time24.append(twoDigitString(s));

	return time24;
}

/**
 * Formats the time in am/pm format
 *
 * \param h, hours 0 to 23
 * \param m, minutes 0 to 59
 * \param s, seconds 0 to 59
 *
 * \return hh:mm:ss A M or hh:mm:ss P M where hh is between 01 and 12, inclusive
 */
std::string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
	std::string str_timeSuffix;
	
	if (h >= 12){
		str_timeSuffix = " P M";
		h -= 12;
	}
	else {
		str_timeSuffix = " A M";
	}
	if (h == 0) {
		h = 12;
	}
	//char buf[100];                                                               // Option 1, line 1: uses C, creates a buffer size for an character array
	//sprintf_s(buf, "%02d:%02d:%02d", h, m, s);                                   // line 2: uses sprintf frtom the C library
	//std::string(buf) + str_timeSuffix;                                           // line 3: returns the buffer converted to a string followed by the timeSuffix

	//return std::format("{:02d}:{:02d}:{:02d}", h, m, s) + str_timeSuffix;        // Option 2: uses C++ 20, simple, and doesn't require the use of twoDigitString(), but not sure if I can use C++ 20

	return formatTime24(h, m, s) + str_timeSuffix;                               // Option 3: works by calling another function followed by the timeSuffix

}

/**
 * centers a string using a padding of witespace on either side
 * 
 * \param widthScreen - desired width of screen, can be set in the printMenu function as screenWidth
 * \param toBeCentered - phrase (as a string) to be centered
 * \return - a string padded by whitespace
 */
std::string center(int widthScreen, std::string toBeCentered) {
	std::string in_str;

	int in_len = toBeCentered.size();

	int left_side = (widthScreen - in_len) / 2;
	int right_side = widthScreen - left_side - in_len;

	std::string out_str = std::string(left_side, ' ') + toBeCentered + std::string(right_side, ' ');
	
	return out_str;
}

// test cases (["Add One Hour", "Add One Minute", "Add One Second", "Exit Program"], 4, 26 or 57)
/**
 * Prints menu
 *
 * \param *strings[] - nonempty array of choices
 * \param width - width of each line, will be comfortably bigger than the longest string
 *
 */
void printMenu(int hh , int mm , int ss) {              // printMenu(char* strings[], unsigned int numStrings, unsigned char width)
	using namespace std;

	system("CLS");                                      // clears console screen

	int screenWidth = 60;

	// created string variables so they can be easily changed and sized
	string chada = "CHADA TECH";
	string hour12 = "12-hour Clock";
	string hour24 = "24-hour Clock";

	// formats and outputs the clocks to the console
	cout << center(screenWidth , chada) << endl;
	cout << center(screenWidth , nCharString(chada.size() + 4, '_')) << "\n\n" << endl;
	cout << nCharString(screenWidth, '_') << endl;
	cout << "|" << nCharString(screenWidth - 2, ' ') << "|" << endl;
	cout << '|' << center(screenWidth / 2 - 2, hour12) << nCharString(2, '|') << center(screenWidth / 2 - 2, hour24) << '|' << endl;
	cout << "|" << nCharString(screenWidth - 2, ' ') << "|" << endl;
	cout << '|' << center(screenWidth / 2 - 2, nCharString(hour12.size() + 4, '-')) << '|';
	cout << '|' << center(screenWidth / 2 - 2, nCharString(hour24.size() + 4, '-')) << '|' << endl;
	cout << "|" << nCharString(screenWidth - 2, ' ') << "|" << endl;
	cout << '|' << center(screenWidth / 2 - 2, formatTime12(hh , mm , ss)) << nCharString(2, '|') << center(screenWidth / 2 - 2, formatTime24(hh , mm , ss)) << '|' << endl;
	cout << "|" << nCharString(screenWidth - 2, ' ') << "|" << endl;
	cout << nCharString(screenWidth , '_') << "\n\n" << endl;


	// created string variables so they can be easily changed and sized
	string OP1 = "1: Increase Hour";
	string OP2 = "2: Increase Minute";
	string OP3 = "3: Increase Second";
	string OP4 = "4: End Program";

	// formats and outputs the menu to the console
	cout << nCharString(screenWidth) << endl;
	cout << "*" << nCharString(screenWidth - 2, ' ') << "*" << endl;
	cout << "*" << center(screenWidth - 2, OP1) << '*' << endl;

	cout << "*" << nCharString(screenWidth - 2, ' ') << "*" << endl;
	cout << "*" << center(screenWidth - 2, OP2) << '*' << endl;
	
	cout << "*" << nCharString(screenWidth - 2, ' ') << "*" << endl;
	cout << "*" << center(screenWidth - 2, OP3) << '*' << endl;
	
	cout << "*" << nCharString(screenWidth - 2, ' ') << "*" << endl;
	cout << "*" << center(screenWidth - 2, OP4) << '*' << endl;

	cout << "*" << nCharString(screenWidth - 2, ' ') << "*" << endl;
	cout << nCharString(screenWidth) << endl;
}

/**
 * Gets menu choice 1 through maxChoice, inclusive
 *
 * \param maxChoice - will be 4 unless program is altered, inclusive
 * \return the first legal choice input, could be 1 through maxChoice (4), inclusive
 */
unsigned int getMenuChoice(unsigned int maxChoice) {
	 // TODO: your code here, 
	int getInput;
	while (true) {
		std::cin >> getInput;
		if (getInput > 0 && getInput <= maxChoice){
			return getInput;
		}
		else {
			std::cout << " Not a valid option, please try again." << std::endl;
 		}
	}
}


/**
 * Adds one second
 * 
 * \param ss - seconds generated in main()
 * \return - seconds + 1
 */
int addOneSecond(int ss) {
	ss = (ss + 1) % 60;
	return ss;
}

/**
 * Adds one minute
 *
 * \param mm - minutes generated in main()
 * \return - minutes + 1
 */
int addOneMinute(int mm) {
	mm = (mm + 1) % 60;
	return mm;
}

/**
 * Adds one hour
 * 
 * \param hh - hours generated in main()
 * \return - hours + 1
 */
int addOneHour(int hh) {
	hh = (hh + 1) % 24;
	return hh;
}



//**************************************************   MAIN   ********************************************************
//********************************************************************************************************************

/**
 * repeats getting the user's choice and taking the appropriate action until the user chooses 4 for exit.
 * 
 * \return 
 */
int main() {

	int hh = getTime(0);
	int mm = getTime(1);
	int ss = getTime(2);
	bool loopRepeat = 1;
	int input = 0;


	printMenu(hh, mm, ss);                             //initial printMenu()

	while (loopRepeat == 1){

		int input = getMenuChoice(4);


		switch (input) {

			case (1):                                  // if input is 1
				hh = addOneHour(hh);
				printMenu(hh , mm , ss);
				break;

			case(2):                                   // if input is 2
				mm = addOneMinute(mm);
				if (mm == 0) {
					hh = addOneHour(hh);
				}
				printMenu(hh, mm, ss);
				break;

			case(3):                                   // if input is 3
				ss = addOneSecond(ss);
				if (ss == 59) {
					mm = addOneMinute(mm);
				}
				printMenu(hh, mm, ss);
				break;

			case(4):                                   // if input is 4
				loopRepeat = 0;
				break;
		}
	}
	return 0;
}