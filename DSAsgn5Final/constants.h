#include <iostream>

using namespace std;

//*** BEGIN - Main Constants and global declarations ******
const int MAX_HOURS = 24;
const int FLT_NUMBER_START = 1000;
const int NO_OF_FLIGHTS = 14;
const int IN_FLTS_HOURLY_SCHEDULE[] = {2, 3, 4, 9, 11, 14, 17, 19, 28, 33, 37, 44, 49, 55};
const string ORIG[] = {"AGR", "AMD", "BLR", "BHO", "BBI", "MAA", "CJB", "DEL", "GOI", "HYD", "IDR",
					   "JLP", "JAI", "JDH"};
const string DESTN[] = {"KNU", "COK", "CCU", "LKO", "IXM", "BOM", "NAG", "PAT", "PNQ", "SHL", "TRV",
						"TRZ", "TCR", "VNS"};
const string DATA_FILE_NAME1 = "servicedFlightsList.txt"; // the data text file name containing the serviced flights details
const string DATA_FILE_NAME2 = "divertedFlightsList.txt"; // the data text file name containing the delayed flights details


const int MAX_NO = 100;
const int MIN_DELAY_INTR = 20;
const int MAX_ADDL_DELAY_INTR = 20;

//*** END - Main Constants and global declarations ******