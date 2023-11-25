#include<iostream>
#include <string>

using namespace std;

const string ASNO = " 23MX13-Data Structures : Presentation Assignment ";
const string STNAME = " Student Name : Lt Col T Varadharajaperumal(Retd) ";
const string STID = " Student Id : 23MX128 ";
const string DUEDT = " Date : Monday, November 27, 2023\n ";

void printReportHeader(ostream &outStream)
{
	system("clear");
	outStream << endl << "\n***** Begining of Report *****" << endl;
	outStream << endl;
	outStream << ASNO << endl;
	outStream << STNAME << endl;
	outStream << STID << endl;
	outStream << DUEDT << endl;
}

void printReportFooter(ostream &outStream)
{
	outStream << endl <<"***** End of report *****" << endl << endl;
}
