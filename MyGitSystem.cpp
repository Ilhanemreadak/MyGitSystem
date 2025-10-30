// mygit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
		std::cout << "\n(En) Warning: You need to give an argument!\n(Tr) Uyari: Bir komut girmelisiniz!\n";

		return 1;
    }

	for (int i = 0; i < argc; i++) {
		std::cout << "Argument " << i << ": " << argv[i] << std::endl;
	}

	string firstCommand = argv[1];

	if (firstCommand == "init") {
		std::cout << "\n(En) Initiliazing mygit repository... \n (Tr) Git deposu baslatiliyor... \n";
		std::filesystem::current_path();

		std::cout << "(En) Current path: \n(Tr) Gecerli dizin: " << std::filesystem::current_path() << "\n";

		std::filesystem::create_directory(".mygit");
		std::filesystem::create_directory(".mygit/objects");
		std::filesystem::create_directory(".mygit/refs");

		std::cout << "(En) Repository initialized!\n(Tr) Git deposu baslatildi!\n";

		return 0;
	}

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
