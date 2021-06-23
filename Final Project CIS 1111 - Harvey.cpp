// Final Project CIS 1111 - Harvey.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Owen Harvey
CIS 1111
12/13/20
This program prompts the user with a menu, from there they can chose if they want to golf 9 or 18 holes, as well as they can choose to eat from a small menu. The user then puts what they want, pays, and moves on to the golf statistics area. Here they will enter their name, how many holes each user played, and what their srokes were. From there they are given scores, put into a category based on performance, and prompted with a thank you message. 
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

float GolferScores(int strokes, int par); //Keep the golfers scores

struct Item {
	Item(const char* n, double v) :
		name(n), value(v)
	{}
	const char* name;
	double value;
};

double getOrder(Item menu[]) //Function to get the order
{
	size_t i;
	double result = 0.0;	// the total of the order
	for (i = 0; menu[i].name; ++i) {
		cout << i + 1 << " - " << menu[i].name
			<< "  " << '$' << menu[i].value << '\n';
	}
	cout << i + 1 << " - " << "End Order\n";

	while (true) {
		unsigned num;
		cout << "Please enter an item number you would like to order(one at a time please): " << flush;
		cin >> num;
		--num;

		if (num > i) {
			cout << "The number you chose isn't on the menu, please enter a number between 1 and 9.\n"; //If they put a number that isn't displayed
		}
		else if (num == i) {
			break;
		}
		else {
			result += menu[num].value;
		}
	}
	return result;
}

void showBill(double bill, double tax, double tip) 
{   //The calculations for the bill, tax, and tip
	cout << "Subtotal : $" << bill << '\n';
	cout << "     tax : $" << tax << '\n';
	cout << "     tip : $" << tip << '\n';
	cout << "   total : $" << tax + tip + bill << '\n';
}

void changeDue(double totBill, double amtTendered)
{   //The amount of change the user is owed, with a little customer service message
	cout << "\n\n\n";
	cout << "Your change is $" << amtTendered - totBill << '\n';
	cout << "\n\n\nExcellent order choices, now you can enter your golf stats!\n\n\n";
}

double getPmt(double total)
{   //User enters how much they are going to pay
	while (true) {
		double amount;
		cout << "Enter payment amount: " << flush;

		cin >> amount;
		if (amount >= total) return amount;
		cout << "You must enter at least $" << total << '\n'; //Option if the amount that is entered is under the amount owed
	}
}

int main()
{
	
	cout << "Welcome to Owen's Ocean Golf Resort!" << endl; //Title of the program
	cout << "------------------------------" << endl; //A line to make the program look a little better :)
	cout << "Below you will enter the amount of holes you played, as well as any food or beverages you might need." << endl;
	cout << "After this you can enter the stats from your round of golf. I hope you had a great time!!" << endl;
	cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
	cout << "\n\n" << endl;
	const int MaximumGolfers = 50;//The most golfers that can be put into the program
	


	//Keeps track of all the inputs
	string golfers[MaximumGolfers];
	int strokes[MaximumGolfers];
	float golfscore[MaximumGolfers];
	int par[MaximumGolfers];
	float final;
	//Intiger and float values of numbers
	int PlayerIndex = {};
	int strokeIndex = {};
	float totalStrokes = {};
	float thePar = {};
	string line;
	ifstream myfile("golfers.txt");
	
		cout << "Owen's Ocean golf menu\n";//Title
		cout << "----------------------\n";
		constexpr double taxRate = 0.065; // tax rate on food
		constexpr double tipRate = 0.30;  // tip on the food bill without tax

		//The menu with the monetary value next to it
		Item menu[]{
		{ "9 holes of golf (par is 27 stokes) ", 8.5 },
		{ "18 holes of golf (par is 72 strokes)", 15.0 },
		{ "Cheeseburger", 4.0 },
		{ "Hotdog", 2.0 },
		{ "Chicken Sandwich", 3.5 },
		{ "Veggie burger", 4.0 },
		{ "Sports drink", 2.0 },
		{ "Water", 1.0 },
		{ nullptr, 0} // Entry to end the order
		};

		cout.setf(std::ios::fixed, ios::floatfield);
		cout.precision(2);

		double subTotal = getOrder(menu);
		double tax = subTotal * taxRate;
		double tip = subTotal * tipRate;

		showBill(subTotal, tax, tip); // Wwhat the showBill function will contain
		double tendered = getPmt(subTotal + tax + tip); //The tendered amount will be the final total. 
		changeDue(subTotal + tax + tip, tendered); // What the changeDue function will contain
	

	char again;
	

	do
	{
		float num;

		cout << "Enter golfer #" << PlayerIndex + 1 << " stats:" << endl; //The player index is going to keep track of the number of the golfers used in program
		cout << "\n";
		cout << "If golfer #" << PlayerIndex + 1 << " entered 9 holes of golf press 1, if you entered 18 holes press 2: ";
		cin >> num;
		if (num == 1) {
			par[PlayerIndex] = 27; //If user puts a 1, the par for 9 holes is used
		}
		if (num == 2) {
			par[PlayerIndex] = 72;//If user puts a 2, the par for 18 holes is used
		}
		cout << "\n";
		
		cout << "Golfer's name: ";
		cin.ignore();//To help getline function correctly in a loop
		getline(cin, golfers[PlayerIndex]);//Keep the names of the golfers



		cout << "Strokes: ";
		cin >> strokes[PlayerIndex];//Keeps the strokes of the golfers


		//If the number of strokes is less than zero
		while (strokes[PlayerIndex] <= 0) {
			cout << "Reenter Strokes : ";
			cin >> strokes[PlayerIndex];
		}
		


		PlayerIndex++; //Adds to the number of golfers


		//If theres less than 50 golfers the user is prompted to either add another golfer or end it
		if (PlayerIndex < MaximumGolfers) {
			cout << "Enter another golfer (y / n) : ";
			cin >> again;
			again = tolower(again);
		}

		cout << endl;



	} while (again == 'y' && PlayerIndex < MaximumGolfers);


	cout << endl;
	cout << "Golfer      Scores" << endl;
	cout << "<><><><><><><><><>" << endl;
	cout << left << fixed << setprecision(1);


	//When the program is ended, the scores are compiled and goffers are prompted with their score and put into a category based on their performence. 
	for (int k = 0; k < PlayerIndex; k++)
	{


		golfscore[k] = GolferScores(strokes[k], par[k]);
		totalStrokes += strokes[k];
		thePar += par[k];



		cout << setw(12) << golfers[k];
		cout << " ";
		cout << golfscore[k] << endl;
		cout << golfscore[k] << (golfscore[k] > 0 ? " You went over par " : (golfscore[k] == 0 ? " You golfed par! Great job " : (golfscore [k] < 0 ? " You golfed under par you are a great golfer!" : " You are the king of Golf"))) << "\n";
		final = golfscore[k];
		if (golfscore[k] < golfscore[strokeIndex]) {
			strokeIndex = k;
		}



	}
	
	
	//Prints the golfer who preformed the best.
	cout << endl << "The best score belongs to: " << golfers[strokeIndex] << ", with a " << golfscore[strokeIndex] << " you are the best!" << endl;
	cout << "Thank you coming to Owen's Ocean Golf Resort! Please come back again soon!\n" << endl; //A little good bye and thank you to the user before it's completley over
	cout << "\n\n\n\n\n\n\n\n";
		myfile.close();
	
	return 0;
}

float GolferScores(int strokes, int par)
{
	float score = float(strokes) - par; //computes the golfers scores by subtracting par from the # of strokes
	return score;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
