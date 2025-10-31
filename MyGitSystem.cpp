// mygit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
int mygit_init();

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
		mygit_init();
	}

}

int mygit_init() { // Initializes a mygit repository in the current directory

	std::cout << "\n(En) Initiliazing mygit repository... (Tr) Git deposu baslatiliyor... \n";

	try {
		std::filesystem::current_path();

		std::cout << "(En) Current path: (Tr) Gecerli dizin: " << std::filesystem::current_path() << "\n";

		std::filesystem::create_directory(".mygit");
		std::filesystem::create_directory(".mygit/objects");
		std::filesystem::create_directory(".mygit/refs");
		std::filesystem::create_directory(".mygit/refs/heads");
		std::filesystem::create_directory(".mygit/refs/tags");

		std::ofstream headFile(".mygit/HEAD"); // This method authomatically creates the file if it does not exist

		if (headFile.is_open()) {
			headFile << "ref: refs/heads/main\n"; // This file points to the current branch and default is main
			headFile.close();
			std::cout << "(En) HEAD file created! (Tr) HEAD dosyasi olusturuldu!\n";
		}
		else {
			std::cout << "(En) Error: Could not create HEAD file! (Tr) Hata: HEAD dosyasi olusturulamadi!\n";
			return 1;
		}

		std::cout << "(En) Repository initialized! (Tr) Git deposu baslatildi!\n";
	}
	catch (const std::filesystem::filesystem_error) {
		std::cout << "(En) Error: While creating git repos an file error accured! (Tr) Hata: Git deposu baslatilirken bir dosya hatasi alindi!\n";
		return 1;
	}
	catch (...) {
		std::cout << "(En) Error: Unknown error accured while creating git repo! (Tr) Hata: Git deposu baslatilirken bilinmeyen bir hata alindi!\n";
		return 1;
	}
	return 0;
}
