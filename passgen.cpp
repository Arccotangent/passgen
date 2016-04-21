#include <iostream>
#include <random>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "passgen <length> <amount> [redundancy in %] [charset]" << endl;
		cout << endl;
		cout << "length - Length of each password in characters" << endl;
		cout << "amount - Amount of passwords to generate" << endl;
		cout << "redundancy (optional) (default 100) - Redundant characters to generate in percent, ex: 100% redundancy generates double the needed chars" << endl;
		cout << "Note: Higher redundancy = Higher entropy, higher security" << endl;
		cout << "charset - Characters to include in passwords, if no charset is specified, it will be customized at runtime" << endl;
		return 1;
	}

	double redundancy_pct = 100;
	int length;
	int amount;
	if (argc == 4)
		redundancy_pct = atof(argv[3]);
	length = atoi(argv[1]);
	amount = atoi(argv[2]);
	string charset;
	int ic = 0;
	if (argc == 5)
	{
		charset = argv[4];
		ic = 1;
	}

	string numbers = "0123456789";
	string lowercase = "abcdefghijklmnopqrstuvwxyz";
	string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string symbols = "!@#$%^&*()_+-={}|[];\"\'<>?,./";
	if (ic == 0)
	{
		cout << "---Character Set Customization---" << endl;
		cout << "Would you like numbers? (y/n) ";
		char yn;
		cin >> yn;
		if (yn == 'y')
		{
			charset += numbers;
			cout << "Added numbers." << endl;
		}
		else
			cout << "Omitted numbers." << endl;
		cout << "Would you like lowercase letters? (y/n) ";
		cin >> yn;
		if (yn == 'y')
		{
			charset += lowercase;
			cout << "Added lowercase letters." << endl;
		}
		else
			cout << "Omitted lowercase letters." << endl;
		cout << "Would you like capital letters? (y/n) ";
		cin >> yn;
		if (yn == 'y')
		{
			charset += uppercase;
			cout << "Added capital letters." << endl;
		}
		else
			cout << "Omitted capital letters." << endl;
		cout << "Would you like symbols? (y/n) ";
		cin >> yn;
		if (yn == 'y')
		{
			charset += symbols;
			cout << "Added symbols." << endl;
		}
		else
			cout << "Omitted symbols." << endl;
		}
	else
	{
		cout << "Skipped character set customization as charset was already defined." << endl;
	}
	
	if (charset.length() == 0 || charset == "")
	{
		cout << "ERROR: Charset cannot be empty." << endl;
		return 2;
	}

	cout << "Generating " << amount << " passwords, each " << length << " characters long, with " << redundancy_pct << "% redundancy." << endl;
	string mempool = "";
	double redundancy = redundancy_pct / 100;
	int needed_chars = length * amount;
	double total_chars_dbl = (double)needed_chars + ((double)needed_chars * redundancy);
	int total_chars = (int)total_chars_dbl;
	double progress;
	cout << "Generating initial memory pool of " << total_chars << " characters." << endl;
	random_device r;

	for (int i = 0; i < total_chars; i++)
	{
		progress = (double)i / (double)total_chars;
		progress *= 100;
		cout << "Memory pool gen: " << i << " / " << total_chars << " (" << progress << "%)\r" << flush;
		mempool += charset.at(r() % charset.length());
	}

	progress = 100.0;
	cout << "Memory pool gen: " << total_chars << " / " << total_chars << " (" << progress << "%)\r" << flush;
	cout << endl;
	cout << "Generating passwords now, with " << needed_chars << " randomly selected characters out of the " << total_chars << " character memory pool." << endl;
	string passwords = "";
	progress = 0.0;

	for (int i = 0; i < needed_chars; i++)
	{
		progress = (double)i / (double)needed_chars;
		progress *= 100;
		cout << "Password gen: " << i << " / " << needed_chars << " (" << progress << "%)\r" << flush;
		passwords += mempool.at(r() % mempool.length());
		if (i % length == length - 1)
			passwords += '\n';
	}

	progress = 100.0;
	cout << "Password gen: " << needed_chars << " / " << needed_chars << " (" << progress << "%)\r" << flush;
	cout << endl;
	cout << "Password generation finished." << endl;
	cout << endl << endl;
	cout << "-----------------------------" << endl;
	cout << passwords << endl;
	return 0;
}
